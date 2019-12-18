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
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  GinPostingList ;

/* Variables and functions */
 int /*<<< orphan*/  SizeOfGinPostingList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginPostingListDecodeAllSegments (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

ItemPointer
ginPostingListDecode(GinPostingList *plist, int *ndecoded)
{
	return ginPostingListDecodeAllSegments(plist,
										   SizeOfGinPostingList(plist),
										   ndecoded);
}