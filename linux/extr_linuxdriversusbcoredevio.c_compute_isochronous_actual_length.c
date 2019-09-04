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
struct urb {unsigned int number_of_packets; TYPE_1__* iso_frame_desc; scalar_t__ actual_length; } ;
struct TYPE_2__ {scalar_t__ actual_length; } ;

/* Variables and functions */

__attribute__((used)) static void compute_isochronous_actual_length(struct urb *urb)
{
	unsigned int i;

	if (urb->number_of_packets > 0) {
		urb->actual_length = 0;
		for (i = 0; i < urb->number_of_packets; i++)
			urb->actual_length +=
					urb->iso_frame_desc[i].actual_length;
	}
}