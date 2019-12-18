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

/* Variables and functions */
 int /*<<< orphan*/  pa_threaded_mainloop_accept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pulseaudio_mainloop ; 

void pulseaudio_accept()
{
	pa_threaded_mainloop_accept(pulseaudio_mainloop);
}