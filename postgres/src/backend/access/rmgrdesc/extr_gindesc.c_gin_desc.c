#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ginxlogVacuumDataLeafPage ;
struct TYPE_9__ {int flags; } ;
typedef  TYPE_2__ ginxlogSplit ;
typedef  int /*<<< orphan*/  ginxlogRecompressDataLeaf ;
struct TYPE_10__ {int /*<<< orphan*/  isDelete; } ;
typedef  TYPE_3__ ginxlogInsertEntry ;
struct TYPE_14__ {int /*<<< orphan*/  key; } ;
struct TYPE_11__ {TYPE_7__ newitem; } ;
typedef  TYPE_4__ ginxlogInsertDataInternal ;
struct TYPE_12__ {int flags; } ;
typedef  TYPE_5__ ginxlogInsert ;
struct TYPE_13__ {char ndeleted; } ;
typedef  TYPE_6__ ginxlogDeleteListPages ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  int /*<<< orphan*/  BlockIdData ;
typedef  int /*<<< orphan*/  BlockId ;

/* Variables and functions */
 int /*<<< orphan*/  BlockIdGetBlockNumber (int /*<<< orphan*/ ) ; 
 int GIN_INSERT_ISDATA ; 
 int GIN_INSERT_ISLEAF ; 
 int GIN_SPLIT_ROOT ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PostingItemGetBlockNumber (TYPE_7__*) ; 
#define  XLOG_GIN_CREATE_PTREE 136 
#define  XLOG_GIN_DELETE_LISTPAGE 135 
#define  XLOG_GIN_DELETE_PAGE 134 
#define  XLOG_GIN_INSERT 133 
#define  XLOG_GIN_INSERT_LISTPAGE 132 
#define  XLOG_GIN_SPLIT 131 
#define  XLOG_GIN_UPDATE_META_PAGE 130 
#define  XLOG_GIN_VACUUM_DATA_LEAF_PAGE 129 
#define  XLOG_GIN_VACUUM_PAGE 128 
 int XLR_INFO_MASK ; 
 int /*<<< orphan*/  XLogRecBlockImageApply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* XLogRecGetBlockData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* XLogRecGetData (int /*<<< orphan*/ *) ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecHasBlockImage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char,...) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  desc_recompress_leaf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
gin_desc(StringInfo buf, XLogReaderState *record)
{
	char	   *rec = XLogRecGetData(record);
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	switch (info)
	{
		case XLOG_GIN_CREATE_PTREE:
			/* no further information */
			break;
		case XLOG_GIN_INSERT:
			{
				ginxlogInsert *xlrec = (ginxlogInsert *) rec;

				appendStringInfo(buf, "isdata: %c isleaf: %c",
								 (xlrec->flags & GIN_INSERT_ISDATA) ? 'T' : 'F',
								 (xlrec->flags & GIN_INSERT_ISLEAF) ? 'T' : 'F');
				if (!(xlrec->flags & GIN_INSERT_ISLEAF))
				{
					char	   *payload = rec + sizeof(ginxlogInsert);
					BlockNumber leftChildBlkno;
					BlockNumber rightChildBlkno;

					leftChildBlkno = BlockIdGetBlockNumber((BlockId) payload);
					payload += sizeof(BlockIdData);
					rightChildBlkno = BlockIdGetBlockNumber((BlockId) payload);
					payload += sizeof(BlockNumber);
					appendStringInfo(buf, " children: %u/%u",
									 leftChildBlkno, rightChildBlkno);
				}
				if (XLogRecHasBlockImage(record, 0))
				{
					if (XLogRecBlockImageApply(record, 0))
						appendStringInfoString(buf, " (full page image)");
					else
						appendStringInfoString(buf, " (full page image, for WAL verification)");
				}
				else
				{
					char	   *payload = XLogRecGetBlockData(record, 0, NULL);

					if (!(xlrec->flags & GIN_INSERT_ISDATA))
						appendStringInfo(buf, " isdelete: %c",
										 (((ginxlogInsertEntry *) payload)->isDelete) ? 'T' : 'F');
					else if (xlrec->flags & GIN_INSERT_ISLEAF)
						desc_recompress_leaf(buf, (ginxlogRecompressDataLeaf *) payload);
					else
					{
						ginxlogInsertDataInternal *insertData =
						(ginxlogInsertDataInternal *) payload;

						appendStringInfo(buf, " pitem: %u-%u/%u",
										 PostingItemGetBlockNumber(&insertData->newitem),
										 ItemPointerGetBlockNumber(&insertData->newitem.key),
										 ItemPointerGetOffsetNumber(&insertData->newitem.key));
					}
				}
			}
			break;
		case XLOG_GIN_SPLIT:
			{
				ginxlogSplit *xlrec = (ginxlogSplit *) rec;

				appendStringInfo(buf, "isrootsplit: %c",
								 (((ginxlogSplit *) rec)->flags & GIN_SPLIT_ROOT) ? 'T' : 'F');
				appendStringInfo(buf, " isdata: %c isleaf: %c",
								 (xlrec->flags & GIN_INSERT_ISDATA) ? 'T' : 'F',
								 (xlrec->flags & GIN_INSERT_ISLEAF) ? 'T' : 'F');
			}
			break;
		case XLOG_GIN_VACUUM_PAGE:
			/* no further information */
			break;
		case XLOG_GIN_VACUUM_DATA_LEAF_PAGE:
			{
				if (XLogRecHasBlockImage(record, 0))
				{
					if (XLogRecBlockImageApply(record, 0))
						appendStringInfoString(buf, " (full page image)");
					else
						appendStringInfoString(buf, " (full page image, for WAL verification)");
				}
				else
				{
					ginxlogVacuumDataLeafPage *xlrec =
					(ginxlogVacuumDataLeafPage *) XLogRecGetBlockData(record, 0, NULL);

					desc_recompress_leaf(buf, &xlrec->data);
				}
			}
			break;
		case XLOG_GIN_DELETE_PAGE:
			/* no further information */
			break;
		case XLOG_GIN_UPDATE_META_PAGE:
			/* no further information */
			break;
		case XLOG_GIN_INSERT_LISTPAGE:
			/* no further information */
			break;
		case XLOG_GIN_DELETE_LISTPAGE:
			appendStringInfo(buf, "ndeleted: %d",
							 ((ginxlogDeleteListPages *) rec)->ndeleted);
			break;
	}
}