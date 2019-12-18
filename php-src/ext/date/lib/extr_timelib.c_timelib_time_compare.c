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
struct TYPE_4__ {scalar_t__ sse; scalar_t__ us; } ;
typedef  TYPE_1__ timelib_time ;

/* Variables and functions */

int timelib_time_compare(timelib_time *t1, timelib_time *t2)
{
	if (t1->sse == t2->sse) {
		if (t1->us == t2->us) {
			return 0;
		}

		return (t1->us < t2->us) ? -1 : 1;
	}

	return (t1->sse < t2->sse) ? -1 : 1;
}