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
struct TYPE_2__ {scalar_t__ curdelta; } ;
typedef  TYPE_1__ SplitPoint ;

/* Variables and functions */

__attribute__((used)) static int
_bt_splitcmp(const void *arg1, const void *arg2)
{
	SplitPoint *split1 = (SplitPoint *) arg1;
	SplitPoint *split2 = (SplitPoint *) arg2;

	if (split1->curdelta > split2->curdelta)
		return 1;
	if (split1->curdelta < split2->curdelta)
		return -1;

	return 0;
}