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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct ceph_snap_realm {int /*<<< orphan*/  ino; } ;
struct ceph_quotarealm_inode {int /*<<< orphan*/  mutex; struct inode* inode; scalar_t__ timeout; } ;
struct ceph_mds_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_STAT_CAP_INODE ; 
 struct inode* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  PTR_ERR (struct inode*) ; 
 int __ceph_do_getattr (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ceph_is_any_caps (struct inode*) ; 
 struct inode* ceph_lookup_inode (struct super_block*,int /*<<< orphan*/ ) ; 
 struct ceph_quotarealm_inode* find_quotarealm_inode (struct ceph_mds_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before_eq (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct inode *lookup_quotarealm_inode(struct ceph_mds_client *mdsc,
					     struct super_block *sb,
					     struct ceph_snap_realm *realm)
{
	struct ceph_quotarealm_inode *qri;
	struct inode *in;

	qri = find_quotarealm_inode(mdsc, realm->ino);
	if (!qri)
		return NULL;

	mutex_lock(&qri->mutex);
	if (qri->inode && ceph_is_any_caps(qri->inode)) {
		/* A request has already returned the inode */
		mutex_unlock(&qri->mutex);
		return qri->inode;
	}
	/* Check if this inode lookup has failed recently */
	if (qri->timeout &&
	    time_before_eq(jiffies, qri->timeout)) {
		mutex_unlock(&qri->mutex);
		return NULL;
	}
	if (qri->inode) {
		/* get caps */
		int ret = __ceph_do_getattr(qri->inode, NULL,
					    CEPH_STAT_CAP_INODE, true);
		if (ret >= 0)
			in = qri->inode;
		else
			in = ERR_PTR(ret);
	}  else {
		in = ceph_lookup_inode(sb, realm->ino);
	}

	if (IS_ERR(in)) {
		pr_warn("Can't lookup inode %llx (err: %ld)\n",
			realm->ino, PTR_ERR(in));
		qri->timeout = jiffies + msecs_to_jiffies(60 * 1000); /* XXX */
	} else {
		qri->timeout = 0;
		qri->inode = in;
	}
	mutex_unlock(&qri->mutex);

	return in;
}