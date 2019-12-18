#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  off; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  GinPlaceToPageRC ;
typedef  TYPE_1__ GinBtreeStack ;
typedef  int /*<<< orphan*/  GinBtreeEntryInsertData ;
typedef  int /*<<< orphan*/  GinBtree ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  GPTP_INSERT ; 
 int /*<<< orphan*/  GPTP_SPLIT ; 
 int /*<<< orphan*/  entryIsEnoughSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entrySplitPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GinPlaceToPageRC
entryBeginPlaceToPage(GinBtree btree, Buffer buf, GinBtreeStack *stack,
					  void *insertPayload, BlockNumber updateblkno,
					  void **ptp_workspace,
					  Page *newlpage, Page *newrpage)
{
	GinBtreeEntryInsertData *insertData = insertPayload;
	OffsetNumber off = stack->off;

	/* If it doesn't fit, deal with split case */
	if (!entryIsEnoughSpace(btree, buf, off, insertData))
	{
		entrySplitPage(btree, buf, stack, insertData, updateblkno,
					   newlpage, newrpage);
		return GPTP_SPLIT;
	}

	/* Else, we're ready to proceed with insertion */
	return GPTP_INSERT;
}