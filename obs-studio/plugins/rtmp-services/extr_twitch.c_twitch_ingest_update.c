#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ array; } ;
struct file_download_data {TYPE_1__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  ingests_loaded ; 
 int /*<<< orphan*/  ingests_refreshed ; 
 int load_ingests (char const*,int) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool twitch_ingest_update(void *param, struct file_download_data *data)
{
	bool success;

	pthread_mutex_lock(&mutex);
	success = load_ingests((const char *)data->buffer.array, true);
	pthread_mutex_unlock(&mutex);

	if (success) {
		os_atomic_set_bool(&ingests_refreshed, true);
		os_atomic_set_bool(&ingests_loaded, true);
	}

	UNUSED_PARAMETER(param);
	return true;
}