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
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Page ;

/* Variables and functions */
 int BRIN_EVACUATE_PAGE ; 
 int /*<<< orphan*/  BRIN_IS_REGULAR_PAGE (int /*<<< orphan*/ ) ; 
 int BrinPageFlags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetFreeSpace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Size
br_page_get_freespace(Page page)
{
	if (!BRIN_IS_REGULAR_PAGE(page) ||
		(BrinPageFlags(page) & BRIN_EVACUATE_PAGE) != 0)
		return 0;
	else
		return PageGetFreeSpace(page);
}