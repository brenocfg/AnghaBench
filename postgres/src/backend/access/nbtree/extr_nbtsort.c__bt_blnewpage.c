#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_4__ {scalar_t__ level; } ;
struct TYPE_6__ {scalar_t__ btpo_cycleid; int /*<<< orphan*/  btpo_flags; TYPE_1__ btpo; int /*<<< orphan*/  btpo_next; int /*<<< orphan*/  btpo_prev; } ;
struct TYPE_5__ {int pd_lower; } ;
typedef  TYPE_2__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  TYPE_3__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  BTP_LEAF ; 
 int /*<<< orphan*/  P_NONE ; 
 scalar_t__ PageGetSpecialPointer (scalar_t__) ; 
 int /*<<< orphan*/  _bt_pageinit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Page
_bt_blnewpage(uint32 level)
{
	Page		page;
	BTPageOpaque opaque;

	page = (Page) palloc(BLCKSZ);

	/* Zero the page and set up standard page header info */
	_bt_pageinit(page, BLCKSZ);

	/* Initialize BT opaque state */
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	opaque->btpo_prev = opaque->btpo_next = P_NONE;
	opaque->btpo.level = level;
	opaque->btpo_flags = (level > 0) ? 0 : BTP_LEAF;
	opaque->btpo_cycleid = 0;

	/* Make the P_HIKEY line pointer appear allocated */
	((PageHeader) page)->pd_lower += sizeof(ItemIdData);

	return page;
}