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
struct fuse_conn {int /*<<< orphan*/  group_id; int /*<<< orphan*/  user_id; int /*<<< orphan*/  user_ns; scalar_t__ allow_other; } ;
struct cred {int /*<<< orphan*/  gid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  egid; int /*<<< orphan*/  uid; int /*<<< orphan*/  suid; int /*<<< orphan*/  euid; } ;

/* Variables and functions */
 struct cred* current_cred () ; 
 int current_in_userns (int /*<<< orphan*/ ) ; 
 scalar_t__ gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fuse_allow_current_process(struct fuse_conn *fc)
{
	const struct cred *cred;

	if (fc->allow_other)
		return current_in_userns(fc->user_ns);

	cred = current_cred();
	if (uid_eq(cred->euid, fc->user_id) &&
	    uid_eq(cred->suid, fc->user_id) &&
	    uid_eq(cred->uid,  fc->user_id) &&
	    gid_eq(cred->egid, fc->group_id) &&
	    gid_eq(cred->sgid, fc->group_id) &&
	    gid_eq(cred->gid,  fc->group_id))
		return 1;

	return 0;
}