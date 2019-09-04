#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* device; scalar_t__ stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  PULSE_DATA (void*) ; 
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 TYPE_1__* data ; 
 int /*<<< orphan*/  pulse_stop_recording (TYPE_1__*) ; 
 int /*<<< orphan*/  pulse_unref () ; 

__attribute__((used)) static void pulse_destroy(void *vptr)
{
	PULSE_DATA(vptr);

	if (!data)
		return;

	if (data->stream)
		pulse_stop_recording(data);
	pulse_unref();

	if (data->device)
		bfree(data->device);
	bfree(data);
}