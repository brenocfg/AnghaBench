#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int uint32 ;
typedef  int XLogRecPtr ;
struct TYPE_25__ {int ReadRecPtr; int max_block_id; TYPE_1__* blocks; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_26__ {int /*<<< orphan*/  bkp_details; } ;
typedef  TYPE_3__ XLogDumpConfig ;
struct TYPE_29__ {int spcNode; int dbNode; int relNode; } ;
struct TYPE_28__ {char* rm_name; char* (* rm_identify ) (int) ;int /*<<< orphan*/  (* rm_desc ) (TYPE_4__*,TYPE_2__*) ;} ;
struct TYPE_27__ {char* data; } ;
struct TYPE_24__ {int bimg_info; int hole_offset; int hole_length; int bimg_len; } ;
typedef  TYPE_4__ StringInfoData ;
typedef  TYPE_5__ RmgrDescData ;
typedef  TYPE_6__ RelFileNode ;
typedef  size_t ForkNumber ;
typedef  int BlockNumber ;

/* Variables and functions */
 int BKPIMAGE_IS_COMPRESSED ; 
 int BLCKSZ ; 
 size_t MAIN_FORKNUM ; 
 TYPE_5__* RmgrDescTable ; 
 int XLR_INFO_MASK ; 
 int /*<<< orphan*/  XLogDumpRecordLen (TYPE_2__*,int*,int*) ; 
 scalar_t__ XLogRecBlockImageApply (TYPE_2__*,int) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,int,TYPE_6__*,size_t*,int*) ; 
 int XLogRecGetInfo (TYPE_2__*) ; 
 int XLogRecGetPrev (TYPE_2__*) ; 
 size_t XLogRecGetRmid (TYPE_2__*) ; 
 int XLogRecGetTotalLen (TYPE_2__*) ; 
 int XLogRecGetXid (TYPE_2__*) ; 
 scalar_t__ XLogRecHasBlockImage (TYPE_2__*,int) ; 
 int /*<<< orphan*/  XLogRecHasBlockRef (TYPE_2__*,int) ; 
 char** forkNames ; 
 int /*<<< orphan*/  initStringInfo (TYPE_4__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 char* stub1 (int) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,TYPE_2__*) ; 

__attribute__((used)) static void
XLogDumpDisplayRecord(XLogDumpConfig *config, XLogReaderState *record)
{
	const char *id;
	const RmgrDescData *desc = &RmgrDescTable[XLogRecGetRmid(record)];
	uint32		rec_len;
	uint32		fpi_len;
	RelFileNode rnode;
	ForkNumber	forknum;
	BlockNumber blk;
	int			block_id;
	uint8		info = XLogRecGetInfo(record);
	XLogRecPtr	xl_prev = XLogRecGetPrev(record);
	StringInfoData s;

	XLogDumpRecordLen(record, &rec_len, &fpi_len);

	printf("rmgr: %-11s len (rec/tot): %6u/%6u, tx: %10u, lsn: %X/%08X, prev %X/%08X, ",
		   desc->rm_name,
		   rec_len, XLogRecGetTotalLen(record),
		   XLogRecGetXid(record),
		   (uint32) (record->ReadRecPtr >> 32), (uint32) record->ReadRecPtr,
		   (uint32) (xl_prev >> 32), (uint32) xl_prev);

	id = desc->rm_identify(info);
	if (id == NULL)
		printf("desc: UNKNOWN (%x) ", info & ~XLR_INFO_MASK);
	else
		printf("desc: %s ", id);

	initStringInfo(&s);
	desc->rm_desc(&s, record);
	printf("%s", s.data);
	pfree(s.data);

	if (!config->bkp_details)
	{
		/* print block references (short format) */
		for (block_id = 0; block_id <= record->max_block_id; block_id++)
		{
			if (!XLogRecHasBlockRef(record, block_id))
				continue;

			XLogRecGetBlockTag(record, block_id, &rnode, &forknum, &blk);
			if (forknum != MAIN_FORKNUM)
				printf(", blkref #%u: rel %u/%u/%u fork %s blk %u",
					   block_id,
					   rnode.spcNode, rnode.dbNode, rnode.relNode,
					   forkNames[forknum],
					   blk);
			else
				printf(", blkref #%u: rel %u/%u/%u blk %u",
					   block_id,
					   rnode.spcNode, rnode.dbNode, rnode.relNode,
					   blk);
			if (XLogRecHasBlockImage(record, block_id))
			{
				if (XLogRecBlockImageApply(record, block_id))
					printf(" FPW");
				else
					printf(" FPW for WAL verification");
			}
		}
		putchar('\n');
	}
	else
	{
		/* print block references (detailed format) */
		putchar('\n');
		for (block_id = 0; block_id <= record->max_block_id; block_id++)
		{
			if (!XLogRecHasBlockRef(record, block_id))
				continue;

			XLogRecGetBlockTag(record, block_id, &rnode, &forknum, &blk);
			printf("\tblkref #%u: rel %u/%u/%u fork %s blk %u",
				   block_id,
				   rnode.spcNode, rnode.dbNode, rnode.relNode,
				   forkNames[forknum],
				   blk);
			if (XLogRecHasBlockImage(record, block_id))
			{
				if (record->blocks[block_id].bimg_info &
					BKPIMAGE_IS_COMPRESSED)
				{
					printf(" (FPW%s); hole: offset: %u, length: %u, "
						   "compression saved: %u",
						   XLogRecBlockImageApply(record, block_id) ?
						   "" : " for WAL verification",
						   record->blocks[block_id].hole_offset,
						   record->blocks[block_id].hole_length,
						   BLCKSZ -
						   record->blocks[block_id].hole_length -
						   record->blocks[block_id].bimg_len);
				}
				else
				{
					printf(" (FPW%s); hole: offset: %u, length: %u",
						   XLogRecBlockImageApply(record, block_id) ?
						   "" : " for WAL verification",
						   record->blocks[block_id].hole_offset,
						   record->blocks[block_id].hole_length);
				}
			}
			putchar('\n');
		}
	}
}