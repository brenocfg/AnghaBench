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
struct TYPE_2__ {struct dentry* dentry; } ;
struct svc_export {int ex_flags; TYPE_1__ ex_path; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  MAY_EXEC ; 
 int NFSEXP_NOSUBTREECHECK ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* dget (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dprintk (char*,struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int inode_permission (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfsd_acceptable(void *expv, struct dentry *dentry)
{
	struct svc_export *exp = expv;
	int rv;
	struct dentry *tdentry;
	struct dentry *parent;

	if (exp->ex_flags & NFSEXP_NOSUBTREECHECK)
		return 1;

	tdentry = dget(dentry);
	while (tdentry != exp->ex_path.dentry && !IS_ROOT(tdentry)) {
		/* make sure parents give x permission to user */
		int err;
		parent = dget_parent(tdentry);
		err = inode_permission(d_inode(parent), MAY_EXEC);
		if (err < 0) {
			dput(parent);
			break;
		}
		dput(tdentry);
		tdentry = parent;
	}
	if (tdentry != exp->ex_path.dentry)
		dprintk("nfsd_acceptable failed at %p %pd\n", tdentry, tdentry);
	rv = (tdentry == exp->ex_path.dentry);
	dput(tdentry);
	return rv;
}