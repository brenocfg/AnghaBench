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

/* Variables and functions */
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 int fls (unsigned long) ; 

__attribute__((used)) static int find_highest_prio_tid(unsigned long tids)
{
	/* lower 3 TIDs aren't ordered perfectly */
	if (tids & 0xF8)
		return fls(tids) - 1;
	/* TID 0 is BE just like TID 3 */
	if (tids & BIT(0))
		return 0;
	return fls(tids) - 1;
}