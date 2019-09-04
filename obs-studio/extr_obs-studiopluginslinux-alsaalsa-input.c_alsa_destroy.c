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
struct alsa_data {struct alsa_data* device; int /*<<< orphan*/  abort_event; scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  _alsa_close (struct alsa_data*) ; 
 int /*<<< orphan*/  bfree (struct alsa_data*) ; 
 int /*<<< orphan*/  os_event_destroy (int /*<<< orphan*/ ) ; 

void alsa_destroy(void *vptr)
{
	struct alsa_data *data = vptr;

	if (data->handle)
		_alsa_close(data);

	os_event_destroy(data->abort_event);
	bfree(data->device);
	bfree(data);
}