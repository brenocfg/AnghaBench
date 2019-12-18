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
struct obs_output {int dummy; } ;
struct obs_encoder {int /*<<< orphan*/  outputs_mutex; int /*<<< orphan*/  outputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_erase_item (int /*<<< orphan*/ ,struct obs_output**) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void obs_encoder_remove_output(struct obs_encoder *encoder,
			       struct obs_output *output)
{
	if (!encoder)
		return;

	pthread_mutex_lock(&encoder->outputs_mutex);
	da_erase_item(encoder->outputs, &output);
	pthread_mutex_unlock(&encoder->outputs_mutex);
}