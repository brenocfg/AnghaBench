#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ center; } ;
typedef  TYPE_1__ gseg_picksplit_item ;

/* Variables and functions */

__attribute__((used)) static int
gseg_picksplit_item_cmp(const void *a, const void *b)
{
	const gseg_picksplit_item *i1 = (const gseg_picksplit_item *) a;
	const gseg_picksplit_item *i2 = (const gseg_picksplit_item *) b;

	if (i1->center < i2->center)
		return -1;
	else if (i1->center == i2->center)
		return 0;
	else
		return 1;
}