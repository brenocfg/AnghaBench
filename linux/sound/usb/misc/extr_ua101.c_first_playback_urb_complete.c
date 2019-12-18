#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct urb {int /*<<< orphan*/  (* complete ) (struct urb*) ;struct ua101* context; } ;
struct ua101 {int /*<<< orphan*/  alsa_playback_wait; int /*<<< orphan*/  states; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLAYBACK_URB_COMPLETED ; 
 int /*<<< orphan*/  playback_urb_complete (struct urb*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void first_playback_urb_complete(struct urb *urb)
{
	struct ua101 *ua = urb->context;

	urb->complete = playback_urb_complete;
	playback_urb_complete(urb);

	set_bit(PLAYBACK_URB_COMPLETED, &ua->states);
	wake_up(&ua->alsa_playback_wait);
}