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
struct jack_data {int /*<<< orphan*/  jack_mutex; struct jack_data* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct jack_data*) ; 
 int /*<<< orphan*/  deactivate_jack (struct jack_data*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jack_destroy(void *vptr)
{
	struct jack_data *data = (struct jack_data *)vptr;

	if (!data)
		return;

	deactivate_jack(data);

	if (data->device)
		bfree(data->device);
	pthread_mutex_destroy(&data->jack_mutex);
	bfree(data);
}