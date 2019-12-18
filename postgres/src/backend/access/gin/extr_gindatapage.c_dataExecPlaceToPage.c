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
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  GinBtreeStack ;
typedef  int /*<<< orphan*/  GinBtree ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dataExecPlaceToPageInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dataExecPlaceToPageLeaf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,void*) ; 

__attribute__((used)) static void
dataExecPlaceToPage(GinBtree btree, Buffer buf, GinBtreeStack *stack,
					void *insertdata, BlockNumber updateblkno,
					void *ptp_workspace)
{
	Page		page = BufferGetPage(buf);

	if (GinPageIsLeaf(page))
		dataExecPlaceToPageLeaf(btree, buf, stack, insertdata,
								ptp_workspace);
	else
		dataExecPlaceToPageInternal(btree, buf, stack, insertdata,
									updateblkno, ptp_workspace);
}