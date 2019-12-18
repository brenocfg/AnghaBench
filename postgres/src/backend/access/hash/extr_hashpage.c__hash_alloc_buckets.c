#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_9__ {int hasho_bucket; int /*<<< orphan*/  hasho_page_id; int /*<<< orphan*/  hasho_flag; scalar_t__ hasho_nextblkno; scalar_t__ hasho_prevblkno; } ;
struct TYPE_8__ {scalar_t__ data; } ;
struct TYPE_7__ {int /*<<< orphan*/  rd_smgr; int /*<<< orphan*/  rd_node; } ;
typedef  TYPE_1__* Relation ;
typedef  scalar_t__ Page ;
typedef  TYPE_2__ PGAlignedBlock ;
typedef  TYPE_3__* HashPageOpaque ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  HASHO_PAGE_ID ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  LH_UNUSED_PAGE ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 scalar_t__ PageGetSpecialPointer (scalar_t__) ; 
 int /*<<< orphan*/  PageSetChecksumInplace (scalar_t__,scalar_t__) ; 
 scalar_t__ RelationNeedsWAL (TYPE_1__*) ; 
 int /*<<< orphan*/  RelationOpenSmgr (TYPE_1__*) ; 
 int /*<<< orphan*/  _hash_pageinit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_newpage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  smgrextend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static bool
_hash_alloc_buckets(Relation rel, BlockNumber firstblock, uint32 nblocks)
{
	BlockNumber lastblock;
	PGAlignedBlock zerobuf;
	Page		page;
	HashPageOpaque ovflopaque;

	lastblock = firstblock + nblocks - 1;

	/*
	 * Check for overflow in block number calculation; if so, we cannot extend
	 * the index anymore.
	 */
	if (lastblock < firstblock || lastblock == InvalidBlockNumber)
		return false;

	page = (Page) zerobuf.data;

	/*
	 * Initialize the page.  Just zeroing the page won't work; see
	 * _hash_freeovflpage for similar usage.  We take care to make the special
	 * space valid for the benefit of tools such as pageinspect.
	 */
	_hash_pageinit(page, BLCKSZ);

	ovflopaque = (HashPageOpaque) PageGetSpecialPointer(page);

	ovflopaque->hasho_prevblkno = InvalidBlockNumber;
	ovflopaque->hasho_nextblkno = InvalidBlockNumber;
	ovflopaque->hasho_bucket = -1;
	ovflopaque->hasho_flag = LH_UNUSED_PAGE;
	ovflopaque->hasho_page_id = HASHO_PAGE_ID;

	if (RelationNeedsWAL(rel))
		log_newpage(&rel->rd_node,
					MAIN_FORKNUM,
					lastblock,
					zerobuf.data,
					true);

	RelationOpenSmgr(rel);
	PageSetChecksumInplace(page, lastblock);
	smgrextend(rel->rd_smgr, MAIN_FORKNUM, lastblock, zerobuf.data, false);

	return true;
}