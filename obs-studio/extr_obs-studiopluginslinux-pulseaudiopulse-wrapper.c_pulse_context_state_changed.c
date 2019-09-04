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
typedef  void pa_context ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  pulse_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pulse_context_state_changed(pa_context *c, void *userdata)
{
	UNUSED_PARAMETER(userdata);
	UNUSED_PARAMETER(c);

	pulse_signal(0);
}