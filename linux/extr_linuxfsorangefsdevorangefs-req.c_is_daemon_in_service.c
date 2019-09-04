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
 int EIO ; 
 int /*<<< orphan*/  devreq_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int open_access_count ; 

int is_daemon_in_service(void)
{
	int in_service;

	/*
	 * What this function does is checks if client-core is alive
	 * based on the access count we maintain on the device.
	 */
	mutex_lock(&devreq_mutex);
	in_service = open_access_count == 1 ? 0 : -EIO;
	mutex_unlock(&devreq_mutex);
	return in_service;
}