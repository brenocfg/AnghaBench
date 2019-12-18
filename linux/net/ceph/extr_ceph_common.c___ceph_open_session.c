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
struct ceph_client {scalar_t__ auth_err; int /*<<< orphan*/  fsid; int /*<<< orphan*/  auth_wq; int /*<<< orphan*/  monc; TYPE_1__* options; } ;
struct TYPE_2__ {unsigned long mount_timeout; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ceph_client_gid (struct ceph_client*) ; 
 int /*<<< orphan*/  ceph_debugfs_client_init (struct ceph_client*) ; 
 long ceph_monc_open_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_timeout_jiffies (unsigned long) ; 
 int /*<<< orphan*/  dout (char*) ; 
 scalar_t__ have_mon_and_osd_map (struct ceph_client*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,unsigned long) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int __ceph_open_session(struct ceph_client *client, unsigned long started)
{
	unsigned long timeout = client->options->mount_timeout;
	long err;

	/* open session, and wait for mon and osd maps */
	err = ceph_monc_open_session(&client->monc);
	if (err < 0)
		return err;

	while (!have_mon_and_osd_map(client)) {
		if (timeout && time_after_eq(jiffies, started + timeout))
			return -ETIMEDOUT;

		/* wait */
		dout("mount waiting for mon_map\n");
		err = wait_event_interruptible_timeout(client->auth_wq,
			have_mon_and_osd_map(client) || (client->auth_err < 0),
			ceph_timeout_jiffies(timeout));
		if (err < 0)
			return err;
		if (client->auth_err < 0)
			return client->auth_err;
	}

	pr_info("client%llu fsid %pU\n", ceph_client_gid(client),
		&client->fsid);
	ceph_debugfs_client_init(client);

	return 0;
}