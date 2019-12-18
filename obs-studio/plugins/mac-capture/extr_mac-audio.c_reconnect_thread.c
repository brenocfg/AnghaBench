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
struct coreaudio_data {int reconnecting; int /*<<< orphan*/  retry_time; int /*<<< orphan*/  exit_event; } ;

/* Variables and functions */
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ coreaudio_init (struct coreaudio_data*) ; 
 scalar_t__ os_event_timedwait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *reconnect_thread(void *param)
{
	struct coreaudio_data *ca = param;

	ca->reconnecting = true;

	while (os_event_timedwait(ca->exit_event, ca->retry_time) ==
	       ETIMEDOUT) {
		if (coreaudio_init(ca))
			break;
	}

	blog(LOG_DEBUG, "coreaudio: exit the reconnect thread");
	ca->reconnecting = false;
	return NULL;
}