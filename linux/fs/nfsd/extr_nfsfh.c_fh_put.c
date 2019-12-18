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
struct svc_fh {struct svc_export* fh_export; struct dentry* fh_dentry; } ;
struct svc_export {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  exp_put (struct svc_export*) ; 
 int /*<<< orphan*/  fh_clear_wcc (struct svc_fh*) ; 
 int /*<<< orphan*/  fh_drop_write (struct svc_fh*) ; 
 int /*<<< orphan*/  fh_unlock (struct svc_fh*) ; 

void
fh_put(struct svc_fh *fhp)
{
	struct dentry * dentry = fhp->fh_dentry;
	struct svc_export * exp = fhp->fh_export;
	if (dentry) {
		fh_unlock(fhp);
		fhp->fh_dentry = NULL;
		dput(dentry);
		fh_clear_wcc(fhp);
	}
	fh_drop_write(fhp);
	if (exp) {
		exp_put(exp);
		fhp->fh_export = NULL;
	}
	return;
}