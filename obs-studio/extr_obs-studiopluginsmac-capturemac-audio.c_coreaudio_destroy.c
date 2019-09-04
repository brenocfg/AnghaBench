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
struct coreaudio_data {struct coreaudio_data* device_uid; struct coreaudio_data* device_name; int /*<<< orphan*/  exit_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct coreaudio_data*) ; 
 int /*<<< orphan*/  coreaudio_shutdown (struct coreaudio_data*) ; 
 int /*<<< orphan*/  os_event_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void coreaudio_destroy(void *data)
{
	struct coreaudio_data *ca = data;

	if (ca) {
		coreaudio_shutdown(ca);

		os_event_destroy(ca->exit_event);
		bfree(ca->device_name);
		bfree(ca->device_uid);
		bfree(ca);
	}
}