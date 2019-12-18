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
struct dentry {int /*<<< orphan*/  d_name; struct dentry* d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  done_seqretry (int /*<<< orphan*/ *,int) ; 
 scalar_t__ need_seqretry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prefetch (struct dentry*) ; 
 int /*<<< orphan*/  prepend (char**,int*,char*,int) ; 
 int prepend_name (char**,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  read_seqbegin_or_lock (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  rename_lock ; 

__attribute__((used)) static char *__dentry_path(struct dentry *d, char *buf, int buflen)
{
	struct dentry *dentry;
	char *end, *retval;
	int len, seq = 0;
	int error = 0;

	if (buflen < 2)
		goto Elong;

	rcu_read_lock();
restart:
	dentry = d;
	end = buf + buflen;
	len = buflen;
	prepend(&end, &len, "\0", 1);
	/* Get '/' right */
	retval = end-1;
	*retval = '/';
	read_seqbegin_or_lock(&rename_lock, &seq);
	while (!IS_ROOT(dentry)) {
		struct dentry *parent = dentry->d_parent;

		prefetch(parent);
		error = prepend_name(&end, &len, &dentry->d_name);
		if (error)
			break;

		retval = end;
		dentry = parent;
	}
	if (!(seq & 1))
		rcu_read_unlock();
	if (need_seqretry(&rename_lock, seq)) {
		seq = 1;
		goto restart;
	}
	done_seqretry(&rename_lock, seq);
	if (error)
		goto Elong;
	return retval;
Elong:
	return ERR_PTR(-ENAMETOOLONG);
}