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
struct usb_line6 {int /*<<< orphan*/  line6pcm; } ;
struct usb_line6_toneport {struct usb_line6 line6; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE6_STREAM_MONITOR ; 
 struct usb_line6_toneport* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line6_pcm_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer ; 
 struct usb_line6_toneport* toneport ; 

__attribute__((used)) static void toneport_start_pcm(struct timer_list *t)
{
	struct usb_line6_toneport *toneport = from_timer(toneport, t, timer);
	struct usb_line6 *line6 = &toneport->line6;

	line6_pcm_acquire(line6->line6pcm, LINE6_STREAM_MONITOR, true);
}