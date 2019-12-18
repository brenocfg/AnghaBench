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
struct TYPE_4__ {int ndigi; scalar_t__ lastrepeat; int /*<<< orphan*/ * calls; } ;
typedef  TYPE_1__ ax25_digi ;

/* Variables and functions */
 scalar_t__ ax25cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ax25digicmp(const ax25_digi *digi1, const ax25_digi *digi2)
{
	int i;

	if (digi1->ndigi != digi2->ndigi)
		return 1;

	if (digi1->lastrepeat != digi2->lastrepeat)
		return 1;

	for (i = 0; i < digi1->ndigi; i++)
		if (ax25cmp(&digi1->calls[i], &digi2->calls[i]) != 0)
			return 1;

	return 0;
}