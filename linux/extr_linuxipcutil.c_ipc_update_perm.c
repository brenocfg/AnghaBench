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
struct kern_ipc_perm {int mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct ipc64_perm {int mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int EINVAL ; 
 int S_IRWXUGO ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

int ipc_update_perm(struct ipc64_perm *in, struct kern_ipc_perm *out)
{
	kuid_t uid = make_kuid(current_user_ns(), in->uid);
	kgid_t gid = make_kgid(current_user_ns(), in->gid);
	if (!uid_valid(uid) || !gid_valid(gid))
		return -EINVAL;

	out->uid = uid;
	out->gid = gid;
	out->mode = (out->mode & ~S_IRWXUGO)
		| (in->mode & S_IRWXUGO);

	return 0;
}