#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {char ntuples; char latestRemovedXid; } ;
typedef  TYPE_1__ xl_hash_vacuum_one_page ;
struct TYPE_15__ {int /*<<< orphan*/  ntuples; } ;
typedef  TYPE_2__ xl_hash_update_meta_page ;
struct TYPE_16__ {int /*<<< orphan*/  is_prim_bucket_same_wrt; int /*<<< orphan*/  ntups; int /*<<< orphan*/  nextblkno; int /*<<< orphan*/  prevblkno; } ;
typedef  TYPE_3__ xl_hash_squeeze_page ;
struct TYPE_17__ {char old_bucket_flag; char new_bucket_flag; } ;
typedef  TYPE_4__ xl_hash_split_complete ;
struct TYPE_18__ {int flags; int /*<<< orphan*/  new_bucket; } ;
typedef  TYPE_5__ xl_hash_split_allocate_page ;
struct TYPE_19__ {char ntups; int /*<<< orphan*/  is_prim_bucket_same_wrt; } ;
typedef  TYPE_6__ xl_hash_move_page_contents ;
struct TYPE_20__ {int /*<<< orphan*/  offnum; } ;
typedef  TYPE_7__ xl_hash_insert ;
struct TYPE_21__ {char num_tuples; char ffactor; } ;
typedef  TYPE_8__ xl_hash_init_meta_page ;
struct TYPE_22__ {int /*<<< orphan*/  bmsize; } ;
typedef  TYPE_9__ xl_hash_init_bitmap_page ;
struct TYPE_12__ {int /*<<< orphan*/  is_primary_bucket_page; int /*<<< orphan*/  clear_dead_marking; } ;
typedef  TYPE_10__ xl_hash_delete ;
struct TYPE_13__ {char bmsize; int /*<<< orphan*/  bmpage_found; } ;
typedef  TYPE_11__ xl_hash_add_ovfl_page ;
typedef  int uint8 ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int XLH_SPLIT_META_UPDATE_MASKS ; 
 int XLH_SPLIT_META_UPDATE_SPLITPOINT ; 
#define  XLOG_HASH_ADD_OVFL_PAGE 138 
#define  XLOG_HASH_DELETE 137 
#define  XLOG_HASH_INIT_BITMAP_PAGE 136 
#define  XLOG_HASH_INIT_META_PAGE 135 
#define  XLOG_HASH_INSERT 134 
#define  XLOG_HASH_MOVE_PAGE_CONTENTS 133 
#define  XLOG_HASH_SPLIT_ALLOCATE_PAGE 132 
#define  XLOG_HASH_SPLIT_COMPLETE 131 
#define  XLOG_HASH_SQUEEZE_PAGE 130 
#define  XLOG_HASH_UPDATE_META_PAGE 129 
#define  XLOG_HASH_VACUUM_ONE_PAGE 128 
 int XLR_INFO_MASK ; 
 char* XLogRecGetData (int /*<<< orphan*/ *) ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char,...) ; 

void
hash_desc(StringInfo buf, XLogReaderState *record)
{
	char	   *rec = XLogRecGetData(record);
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	switch (info)
	{
		case XLOG_HASH_INIT_META_PAGE:
			{
				xl_hash_init_meta_page *xlrec = (xl_hash_init_meta_page *) rec;

				appendStringInfo(buf, "num_tuples %g, fillfactor %d",
								 xlrec->num_tuples, xlrec->ffactor);
				break;
			}
		case XLOG_HASH_INIT_BITMAP_PAGE:
			{
				xl_hash_init_bitmap_page *xlrec = (xl_hash_init_bitmap_page *) rec;

				appendStringInfo(buf, "bmsize %d", xlrec->bmsize);
				break;
			}
		case XLOG_HASH_INSERT:
			{
				xl_hash_insert *xlrec = (xl_hash_insert *) rec;

				appendStringInfo(buf, "off %u", xlrec->offnum);
				break;
			}
		case XLOG_HASH_ADD_OVFL_PAGE:
			{
				xl_hash_add_ovfl_page *xlrec = (xl_hash_add_ovfl_page *) rec;

				appendStringInfo(buf, "bmsize %d, bmpage_found %c",
								 xlrec->bmsize, (xlrec->bmpage_found) ? 'T' : 'F');
				break;
			}
		case XLOG_HASH_SPLIT_ALLOCATE_PAGE:
			{
				xl_hash_split_allocate_page *xlrec = (xl_hash_split_allocate_page *) rec;

				appendStringInfo(buf, "new_bucket %u, meta_page_masks_updated %c, issplitpoint_changed %c",
								 xlrec->new_bucket,
								 (xlrec->flags & XLH_SPLIT_META_UPDATE_MASKS) ? 'T' : 'F',
								 (xlrec->flags & XLH_SPLIT_META_UPDATE_SPLITPOINT) ? 'T' : 'F');
				break;
			}
		case XLOG_HASH_SPLIT_COMPLETE:
			{
				xl_hash_split_complete *xlrec = (xl_hash_split_complete *) rec;

				appendStringInfo(buf, "old_bucket_flag %u, new_bucket_flag %u",
								 xlrec->old_bucket_flag, xlrec->new_bucket_flag);
				break;
			}
		case XLOG_HASH_MOVE_PAGE_CONTENTS:
			{
				xl_hash_move_page_contents *xlrec = (xl_hash_move_page_contents *) rec;

				appendStringInfo(buf, "ntups %d, is_primary %c",
								 xlrec->ntups,
								 xlrec->is_prim_bucket_same_wrt ? 'T' : 'F');
				break;
			}
		case XLOG_HASH_SQUEEZE_PAGE:
			{
				xl_hash_squeeze_page *xlrec = (xl_hash_squeeze_page *) rec;

				appendStringInfo(buf, "prevblkno %u, nextblkno %u, ntups %d, is_primary %c",
								 xlrec->prevblkno,
								 xlrec->nextblkno,
								 xlrec->ntups,
								 xlrec->is_prim_bucket_same_wrt ? 'T' : 'F');
				break;
			}
		case XLOG_HASH_DELETE:
			{
				xl_hash_delete *xlrec = (xl_hash_delete *) rec;

				appendStringInfo(buf, "clear_dead_marking %c, is_primary %c",
								 xlrec->clear_dead_marking ? 'T' : 'F',
								 xlrec->is_primary_bucket_page ? 'T' : 'F');
				break;
			}
		case XLOG_HASH_UPDATE_META_PAGE:
			{
				xl_hash_update_meta_page *xlrec = (xl_hash_update_meta_page *) rec;

				appendStringInfo(buf, "ntuples %g",
								 xlrec->ntuples);
				break;
			}
		case XLOG_HASH_VACUUM_ONE_PAGE:
			{
				xl_hash_vacuum_one_page *xlrec = (xl_hash_vacuum_one_page *) rec;

				appendStringInfo(buf, "ntuples %d, latest removed xid %u",
								 xlrec->ntuples,
								 xlrec->latestRemovedXid);
				break;
			}
	}
}