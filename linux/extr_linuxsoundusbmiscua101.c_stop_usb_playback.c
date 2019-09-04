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
struct ua101 {int /*<<< orphan*/  playback_tasklet; int /*<<< orphan*/  playback; int /*<<< orphan*/  states; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTF_PLAYBACK ; 
 int /*<<< orphan*/  USB_PLAYBACK_RUNNING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_iso_interface (struct ua101*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_stream_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_usb_playback(struct ua101 *ua)
{
	clear_bit(USB_PLAYBACK_RUNNING, &ua->states);

	kill_stream_urbs(&ua->playback);

	tasklet_kill(&ua->playback_tasklet);

	disable_iso_interface(ua, INTF_PLAYBACK);
}