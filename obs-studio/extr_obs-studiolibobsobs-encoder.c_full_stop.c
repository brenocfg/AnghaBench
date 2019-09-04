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
struct obs_encoder {int /*<<< orphan*/  callbacks_mutex; int /*<<< orphan*/  callbacks; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_connection (struct obs_encoder*) ; 

void full_stop(struct obs_encoder *encoder)
{
	if (encoder) {
		pthread_mutex_lock(&encoder->callbacks_mutex);
		da_free(encoder->callbacks);
		remove_connection(encoder);
		pthread_mutex_unlock(&encoder->callbacks_mutex);
	}
}