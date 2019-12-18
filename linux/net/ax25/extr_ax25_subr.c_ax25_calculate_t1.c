#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int backoff; int n2count; int t1; int rtt; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */

void ax25_calculate_t1(ax25_cb *ax25)
{
	int n, t = 2;

	switch (ax25->backoff) {
	case 0:
		break;

	case 1:
		t += 2 * ax25->n2count;
		break;

	case 2:
		for (n = 0; n < ax25->n2count; n++)
			t *= 2;
		if (t > 8) t = 8;
		break;
	}

	ax25->t1 = t * ax25->rtt;
}