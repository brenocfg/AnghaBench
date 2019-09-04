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
struct svc_export {int dummy; } ;
struct path {struct dentry* dentry; } ;
struct dentry {int dummy; } ;
struct cache_detail {int dummy; } ;
struct auth_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  PTR_ERR (struct svc_export*) ; 
 struct dentry* dget (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct svc_export* exp_get_by_name (struct cache_detail*,struct auth_domain*,struct path*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct svc_export *
exp_parent(struct cache_detail *cd, struct auth_domain *clp, struct path *path)
{
	struct dentry *saved = dget(path->dentry);
	struct svc_export *exp = exp_get_by_name(cd, clp, path, NULL);

	while (PTR_ERR(exp) == -ENOENT && !IS_ROOT(path->dentry)) {
		struct dentry *parent = dget_parent(path->dentry);
		dput(path->dentry);
		path->dentry = parent;
		exp = exp_get_by_name(cd, clp, path, NULL);
	}
	dput(path->dentry);
	path->dentry = saved;
	return exp;
}