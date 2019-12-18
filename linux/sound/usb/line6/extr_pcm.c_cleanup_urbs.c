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
struct line6_pcm_stream {scalar_t__* urbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  usb_free_urb (scalar_t__) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

__attribute__((used)) static void cleanup_urbs(struct line6_pcm_stream *pcms, int iso_buffers)
{
	int i;

	/* Most likely impossible in current code... */
	if (pcms->urbs == NULL)
		return;

	for (i = 0; i < iso_buffers; i++) {
		if (pcms->urbs[i]) {
			usb_kill_urb(pcms->urbs[i]);
			usb_free_urb(pcms->urbs[i]);
		}
	}
	kfree(pcms->urbs);
	pcms->urbs = NULL;
}