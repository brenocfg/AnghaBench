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
struct ceph_fsid {int dummy; } ;
struct ceph_client {int /*<<< orphan*/  fsid; scalar_t__ have_fsid; } ;

/* Variables and functions */
 scalar_t__ ceph_fsid_compare (int /*<<< orphan*/ *,struct ceph_fsid*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ceph_fsid*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ *,struct ceph_fsid*) ; 

int ceph_check_fsid(struct ceph_client *client, struct ceph_fsid *fsid)
{
	if (client->have_fsid) {
		if (ceph_fsid_compare(&client->fsid, fsid)) {
			pr_err("bad fsid, had %pU got %pU",
			       &client->fsid, fsid);
			return -1;
		}
	} else {
		memcpy(&client->fsid, fsid, sizeof(*fsid));
	}
	return 0;
}