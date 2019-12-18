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
struct alsa_data {int /*<<< orphan*/  reopen; int /*<<< orphan*/  abort_event; } ;

/* Variables and functions */
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int REOPEN_TIMEOUT ; 
 scalar_t__ _alsa_open (struct alsa_data*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 scalar_t__ os_event_timedwait (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 

void *_alsa_reopen(void *attr)
{
	struct alsa_data *data = attr;
	unsigned long timeout = REOPEN_TIMEOUT;

	blog(LOG_DEBUG, "Reopen thread started.");

	os_atomic_set_bool(&data->reopen, true);

	while (os_event_timedwait(data->abort_event, timeout) == ETIMEDOUT) {
		if (_alsa_open(data))
			break;

		if (timeout < (REOPEN_TIMEOUT * 5))
			timeout += REOPEN_TIMEOUT;
	}

	os_atomic_set_bool(&data->reopen, false);

	blog(LOG_DEBUG, "Reopen thread is about to exit.");

	pthread_exit(NULL);
	return NULL;
}