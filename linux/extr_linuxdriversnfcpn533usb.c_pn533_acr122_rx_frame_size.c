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
struct TYPE_2__ {int datalen; } ;
struct pn533_acr122_rx_frame {TYPE_1__ ccid; } ;

/* Variables and functions */

__attribute__((used)) static int pn533_acr122_rx_frame_size(void *frame)
{
	struct pn533_acr122_rx_frame *f = frame;

	/* f->ccid.datalen already includes tail length */
	return sizeof(struct pn533_acr122_rx_frame) + f->ccid.datalen;
}