#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dentry {int dummy; } ;
struct TYPE_4__ {TYPE_1__* head; } ;
struct ceph_mds_request {struct dentry* r_dentry; TYPE_2__ r_reply_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  is_dentry; } ;

/* Variables and functions */
 int ENOENT ; 
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  d_add (struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 struct dentry* dget (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,struct dentry*,int /*<<< orphan*/ ) ; 

struct dentry *ceph_finish_lookup(struct ceph_mds_request *req,
				  struct dentry *dentry, int err)
{
	if (err == -ENOENT) {
		/* no trace? */
		err = 0;
		if (!req->r_reply_info.head->is_dentry) {
			dout("ENOENT and no trace, dentry %p inode %p\n",
			     dentry, d_inode(dentry));
			if (d_really_is_positive(dentry)) {
				d_drop(dentry);
				err = -ENOENT;
			} else {
				d_add(dentry, NULL);
			}
		}
	}
	if (err)
		dentry = ERR_PTR(err);
	else if (dentry != req->r_dentry)
		dentry = dget(req->r_dentry);   /* we got spliced */
	else
		dentry = NULL;
	return dentry;
}