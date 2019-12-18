#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int float8 ;
struct TYPE_11__ {scalar_t__ rd_options; } ;
struct TYPE_10__ {scalar_t__ btm_version; int btm_last_cleanup_num_heap_tuples; int /*<<< orphan*/  btm_oldest_btpo_xact; } ;
struct TYPE_9__ {int num_heap_tuples; TYPE_5__* index; } ;
struct TYPE_8__ {scalar_t__ vacuum_cleanup_index_scale_factor; } ;
typedef  TYPE_1__ StdRdOptions ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_2__ IndexVacuumInfo ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_3__ BTMetaPageData ;

/* Variables and functions */
 TYPE_3__* BTPageGetMeta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTREE_METAPAGE ; 
 scalar_t__ BTREE_NOVAC_VERSION ; 
 int /*<<< orphan*/  BT_READ ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecentGlobalXmin ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_getbuf (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relbuf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int vacuum_cleanup_index_scale_factor ; 

__attribute__((used)) static bool
_bt_vacuum_needs_cleanup(IndexVacuumInfo *info)
{
	Buffer		metabuf;
	Page		metapg;
	BTMetaPageData *metad;
	bool		result = false;

	metabuf = _bt_getbuf(info->index, BTREE_METAPAGE, BT_READ);
	metapg = BufferGetPage(metabuf);
	metad = BTPageGetMeta(metapg);

	if (metad->btm_version < BTREE_NOVAC_VERSION)
	{
		/*
		 * Do cleanup if metapage needs upgrade, because we don't have
		 * cleanup-related meta-information yet.
		 */
		result = true;
	}
	else if (TransactionIdIsValid(metad->btm_oldest_btpo_xact) &&
			 TransactionIdPrecedes(metad->btm_oldest_btpo_xact,
								   RecentGlobalXmin))
	{
		/*
		 * If oldest btpo.xact in the deleted pages is older than
		 * RecentGlobalXmin, then at least one deleted page can be recycled.
		 */
		result = true;
	}
	else
	{
		StdRdOptions *relopts;
		float8		cleanup_scale_factor;
		float8		prev_num_heap_tuples;

		/*
		 * If table receives enough insertions and no cleanup was performed,
		 * then index would appear have stale statistics.  If scale factor is
		 * set, we avoid that by performing cleanup if the number of inserted
		 * tuples exceeds vacuum_cleanup_index_scale_factor fraction of
		 * original tuples count.
		 */
		relopts = (StdRdOptions *) info->index->rd_options;
		cleanup_scale_factor = (relopts &&
								relopts->vacuum_cleanup_index_scale_factor >= 0)
			? relopts->vacuum_cleanup_index_scale_factor
			: vacuum_cleanup_index_scale_factor;
		prev_num_heap_tuples = metad->btm_last_cleanup_num_heap_tuples;

		if (cleanup_scale_factor <= 0 ||
			prev_num_heap_tuples <= 0 ||
			(info->num_heap_tuples - prev_num_heap_tuples) /
			prev_num_heap_tuples >= cleanup_scale_factor)
			result = true;
	}

	_bt_relbuf(info->index, metabuf);
	return result;
}