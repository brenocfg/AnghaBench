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

/* Variables and functions */
 int /*<<< orphan*/  LINE6_STREAM_MONITOR ; 
 int /*<<< orphan*/  line6_pcm_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void toneport_startup(struct usb_line6 *line6)
{
	line6_pcm_acquire(line6->line6pcm, LINE6_STREAM_MONITOR, true);
}