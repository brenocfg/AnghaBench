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

/* Variables and functions */
 int /*<<< orphan*/  free_ingests () ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twitch_update_info ; 
 int /*<<< orphan*/  update_info_destroy (int /*<<< orphan*/ ) ; 

void unload_twitch_data(void)
{
	update_info_destroy(twitch_update_info);
	free_ingests();
	pthread_mutex_destroy(&mutex);
}