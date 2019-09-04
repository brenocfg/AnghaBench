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
struct svc_fh {int /*<<< orphan*/  fh_handle; } ;
struct svc_export {int dummy; } ;
struct path {int /*<<< orphan*/  dentry; } ;
struct nfsd_net {struct cache_detail* svc_export_cache; } ;
struct net {int dummy; } ;
struct knfsd_fh {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct cache_detail {int dummy; } ;
struct auth_domain {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct svc_export*) ; 
 int PTR_ERR (struct svc_export*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct svc_export* exp_parent (struct cache_detail*,struct auth_domain*,struct path*) ; 
 int /*<<< orphan*/  exp_put (struct svc_export*) ; 
 scalar_t__ fh_compose (struct svc_fh*,struct svc_export*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fh_init (struct svc_fh*,int) ; 
 int /*<<< orphan*/  fh_put (struct svc_fh*) ; 
 scalar_t__ kern_path (char*,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  memcpy (struct knfsd_fh*,int /*<<< orphan*/ *,int) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  printk (char*,char*) ; 

int
exp_rootfh(struct net *net, struct auth_domain *clp, char *name,
	   struct knfsd_fh *f, int maxsize)
{
	struct svc_export	*exp;
	struct path		path;
	struct inode		*inode;
	struct svc_fh		fh;
	int			err;
	struct nfsd_net		*nn = net_generic(net, nfsd_net_id);
	struct cache_detail	*cd = nn->svc_export_cache;

	err = -EPERM;
	/* NB: we probably ought to check that it's NUL-terminated */
	if (kern_path(name, 0, &path)) {
		printk("nfsd: exp_rootfh path not found %s", name);
		return err;
	}
	inode = d_inode(path.dentry);

	dprintk("nfsd: exp_rootfh(%s [%p] %s:%s/%ld)\n",
		 name, path.dentry, clp->name,
		 inode->i_sb->s_id, inode->i_ino);
	exp = exp_parent(cd, clp, &path);
	if (IS_ERR(exp)) {
		err = PTR_ERR(exp);
		goto out;
	}

	/*
	 * fh must be initialized before calling fh_compose
	 */
	fh_init(&fh, maxsize);
	if (fh_compose(&fh, exp, path.dentry, NULL))
		err = -EINVAL;
	else
		err = 0;
	memcpy(f, &fh.fh_handle, sizeof(struct knfsd_fh));
	fh_put(&fh);
	exp_put(exp);
out:
	path_put(&path);
	return err;
}