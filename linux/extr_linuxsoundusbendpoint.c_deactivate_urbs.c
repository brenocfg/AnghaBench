#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct urb {int dummy; } ;
struct snd_usb_endpoint {unsigned int nurbs; TYPE_1__* urb; int /*<<< orphan*/  unlink_mask; int /*<<< orphan*/  active_mask; scalar_t__ next_packet_write_pos; scalar_t__ next_packet_read_pos; int /*<<< orphan*/  ready_playback_urbs; int /*<<< orphan*/  flags; TYPE_2__* chip; } ;
struct TYPE_4__ {int /*<<< orphan*/  shutdown; } ;
struct TYPE_3__ {struct urb* urb; } ;

/* Variables and functions */
 int EBADFD ; 
 int /*<<< orphan*/  EP_FLAG_RUNNING ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_unlink_urb (struct urb*) ; 

__attribute__((used)) static int deactivate_urbs(struct snd_usb_endpoint *ep, bool force)
{
	unsigned int i;

	if (!force && atomic_read(&ep->chip->shutdown)) /* to be sure... */
		return -EBADFD;

	clear_bit(EP_FLAG_RUNNING, &ep->flags);

	INIT_LIST_HEAD(&ep->ready_playback_urbs);
	ep->next_packet_read_pos = 0;
	ep->next_packet_write_pos = 0;

	for (i = 0; i < ep->nurbs; i++) {
		if (test_bit(i, &ep->active_mask)) {
			if (!test_and_set_bit(i, &ep->unlink_mask)) {
				struct urb *u = ep->urb[i].urb;
				usb_unlink_urb(u);
			}
		}
	}

	return 0;
}