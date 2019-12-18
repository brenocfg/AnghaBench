#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ndigi; int lastrepeat; int* repeated; TYPE_1__* calls; } ;
typedef  TYPE_2__ ax25_digi ;
struct TYPE_5__ {int /*<<< orphan*/ * ax25_call; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_HBIT ; 

void ax25_digi_invert(const ax25_digi *in, ax25_digi *out)
{
	int ct;

	out->ndigi      = in->ndigi;
	out->lastrepeat = in->ndigi - in->lastrepeat - 2;

	/* Invert the digipeaters */
	for (ct = 0; ct < in->ndigi; ct++) {
		out->calls[ct] = in->calls[in->ndigi - ct - 1];

		if (ct <= out->lastrepeat) {
			out->calls[ct].ax25_call[6] |= AX25_HBIT;
			out->repeated[ct]            = 1;
		} else {
			out->calls[ct].ax25_call[6] &= ~AX25_HBIT;
			out->repeated[ct]            = 0;
		}
	}
}