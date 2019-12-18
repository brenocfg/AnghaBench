#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PostingItem ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  GinPlaceToPageRC ;
typedef  int /*<<< orphan*/  GinBtreeStack ;
typedef  int /*<<< orphan*/  GinBtree ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPTP_INSERT ; 
 int /*<<< orphan*/  GPTP_SPLIT ; 
 int GinNonLeafDataPageGetFreeSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dataSplitPageInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GinPlaceToPageRC
dataBeginPlaceToPageInternal(GinBtree btree, Buffer buf, GinBtreeStack *stack,
							 void *insertdata, BlockNumber updateblkno,
							 void **ptp_workspace,
							 Page *newlpage, Page *newrpage)
{
	Page		page = BufferGetPage(buf);

	/* If it doesn't fit, deal with split case */
	if (GinNonLeafDataPageGetFreeSpace(page) < sizeof(PostingItem))
	{
		dataSplitPageInternal(btree, buf, stack, insertdata, updateblkno,
							  newlpage, newrpage);
		return GPTP_SPLIT;
	}

	/* Else, we're ready to proceed with insertion */
	return GPTP_INSERT;
}