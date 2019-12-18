#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  callback_mutex; int /*<<< orphan*/  callbacks; } ;
typedef  TYPE_1__ obs_fader_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_fader_detach_source (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void obs_fader_destroy(obs_fader_t *fader)
{
	if (!fader)
		return;

	obs_fader_detach_source(fader);
	da_free(fader->callbacks);
	pthread_mutex_destroy(&fader->callback_mutex);
	pthread_mutex_destroy(&fader->mutex);

	bfree(fader);
}