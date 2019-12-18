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
struct vfsmount {struct dentry* mnt_root; } ;
struct qstr {char* name; void* len; } ;
struct dentry {int dummy; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 struct dentry* d_hash_and_lookup (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  d_invalidate (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 void* snprintf (char*,int,char*,int) ; 
 void* strlen (char*) ; 

__attribute__((used)) static void proc_flush_task_mnt(struct vfsmount *mnt, pid_t pid, pid_t tgid)
{
	struct dentry *dentry, *leader, *dir;
	char buf[10 + 1];
	struct qstr name;

	name.name = buf;
	name.len = snprintf(buf, sizeof(buf), "%u", pid);
	/* no ->d_hash() rejects on procfs */
	dentry = d_hash_and_lookup(mnt->mnt_root, &name);
	if (dentry) {
		d_invalidate(dentry);
		dput(dentry);
	}

	if (pid == tgid)
		return;

	name.name = buf;
	name.len = snprintf(buf, sizeof(buf), "%u", tgid);
	leader = d_hash_and_lookup(mnt->mnt_root, &name);
	if (!leader)
		goto out;

	name.name = "task";
	name.len = strlen(name.name);
	dir = d_hash_and_lookup(leader, &name);
	if (!dir)
		goto out_put_leader;

	name.name = buf;
	name.len = snprintf(buf, sizeof(buf), "%u", pid);
	dentry = d_hash_and_lookup(dir, &name);
	if (dentry) {
		d_invalidate(dentry);
		dput(dentry);
	}

	dput(dir);
out_put_leader:
	dput(leader);
out:
	return;
}