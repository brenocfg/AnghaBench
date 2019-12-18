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
struct ceph_client {int /*<<< orphan*/  mount_mutex; } ;

/* Variables and functions */
 int __ceph_open_session (struct ceph_client*,unsigned long) ; 
 int /*<<< orphan*/  dout (char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ceph_open_session(struct ceph_client *client)
{
	int ret;
	unsigned long started = jiffies;  /* note the start time */

	dout("open_session start\n");
	mutex_lock(&client->mount_mutex);

	ret = __ceph_open_session(client, started);

	mutex_unlock(&client->mount_mutex);
	return ret;
}