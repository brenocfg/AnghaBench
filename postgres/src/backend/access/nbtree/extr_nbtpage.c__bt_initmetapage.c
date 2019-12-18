#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32 ;
struct TYPE_7__ {double btm_last_cleanup_num_heap_tuples; int /*<<< orphan*/  btm_oldest_btpo_xact; void* btm_fastlevel; void* btm_fastroot; void* btm_level; void* btm_root; int /*<<< orphan*/  btm_version; int /*<<< orphan*/  btm_magic; } ;
struct TYPE_6__ {int /*<<< orphan*/  btpo_flags; } ;
struct TYPE_5__ {int pd_lower; } ;
typedef  TYPE_1__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  void* BlockNumber ;
typedef  TYPE_2__* BTPageOpaque ;
typedef  TYPE_3__ BTMetaPageData ;

/* Variables and functions */
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  BTP_META ; 
 TYPE_3__* BTPageGetMeta (scalar_t__) ; 
 int /*<<< orphan*/  BTREE_MAGIC ; 
 int /*<<< orphan*/  BTREE_VERSION ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 scalar_t__ PageGetSpecialPointer (scalar_t__) ; 
 int /*<<< orphan*/  _bt_pageinit (scalar_t__,int /*<<< orphan*/ ) ; 

void
_bt_initmetapage(Page page, BlockNumber rootbknum, uint32 level)
{
	BTMetaPageData *metad;
	BTPageOpaque metaopaque;

	_bt_pageinit(page, BLCKSZ);

	metad = BTPageGetMeta(page);
	metad->btm_magic = BTREE_MAGIC;
	metad->btm_version = BTREE_VERSION;
	metad->btm_root = rootbknum;
	metad->btm_level = level;
	metad->btm_fastroot = rootbknum;
	metad->btm_fastlevel = level;
	metad->btm_oldest_btpo_xact = InvalidTransactionId;
	metad->btm_last_cleanup_num_heap_tuples = -1.0;

	metaopaque = (BTPageOpaque) PageGetSpecialPointer(page);
	metaopaque->btpo_flags = BTP_META;

	/*
	 * Set pd_lower just past the end of the metadata.  This is essential,
	 * because without doing so, metadata will be lost if xlog.c compresses
	 * the page.
	 */
	((PageHeader) page)->pd_lower =
		((char *) metad + sizeof(BTMetaPageData)) - (char *) page;
}