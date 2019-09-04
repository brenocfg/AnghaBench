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
struct acm {int rx_buflimit; int /*<<< orphan*/ * read_urbs; TYPE_1__* wb; int /*<<< orphan*/  ctrlurb; } ;
struct TYPE_2__ {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int ACM_NW ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acm_kill_urbs(struct acm *acm)
{
	int i;

	usb_kill_urb(acm->ctrlurb);
	for (i = 0; i < ACM_NW; i++)
		usb_kill_urb(acm->wb[i].urb);
	for (i = 0; i < acm->rx_buflimit; i++)
		usb_kill_urb(acm->read_urbs[i]);
}