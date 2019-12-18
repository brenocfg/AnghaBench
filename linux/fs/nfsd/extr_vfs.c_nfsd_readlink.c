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
struct svc_rqst {int dummy; } ;
struct svc_fh {int /*<<< orphan*/  fh_dentry; TYPE_2__* fh_export; } ;
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;
typedef  int __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  mnt; } ;
struct TYPE_4__ {TYPE_1__ ex_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_DELAYED_CALL (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (char const*) ; 
 int /*<<< orphan*/  NFSD_MAY_NOP ; 
 int /*<<< orphan*/  PTR_ERR (char const*) ; 
 int /*<<< orphan*/  S_IFLNK ; 
 int /*<<< orphan*/  d_is_symlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_delayed_call (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  done ; 
 int fh_verify (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int nfserr_inval ; 
 int nfserrno (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  touch_atime (struct path*) ; 
 scalar_t__ unlikely (int) ; 
 char* vfs_get_link (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__be32
nfsd_readlink(struct svc_rqst *rqstp, struct svc_fh *fhp, char *buf, int *lenp)
{
	__be32		err;
	const char *link;
	struct path path;
	DEFINE_DELAYED_CALL(done);
	int len;

	err = fh_verify(rqstp, fhp, S_IFLNK, NFSD_MAY_NOP);
	if (unlikely(err))
		return err;

	path.mnt = fhp->fh_export->ex_path.mnt;
	path.dentry = fhp->fh_dentry;

	if (unlikely(!d_is_symlink(path.dentry)))
		return nfserr_inval;

	touch_atime(&path);

	link = vfs_get_link(path.dentry, &done);
	if (IS_ERR(link))
		return nfserrno(PTR_ERR(link));

	len = strlen(link);
	if (len < *lenp)
		*lenp = len;
	memcpy(buf, link, *lenp);
	do_delayed_call(&done);
	return 0;
}