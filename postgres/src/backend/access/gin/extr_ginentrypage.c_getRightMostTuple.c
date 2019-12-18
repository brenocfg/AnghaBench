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
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  IndexTuple ;

/* Variables and functions */
 int /*<<< orphan*/  PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 

__attribute__((used)) static IndexTuple
getRightMostTuple(Page page)
{
	OffsetNumber maxoff = PageGetMaxOffsetNumber(page);

	return (IndexTuple) PageGetItem(page, PageGetItemId(page, maxoff));
}