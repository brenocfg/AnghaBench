#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct user_namespace {int dummy; } ;
struct timespec64 {int tv_nsec; scalar_t__ tv_sec; } ;
struct svc_rqst {int dummy; } ;
struct svc_fh {TYPE_1__* fh_export; struct dentry* fh_dentry; } ;
struct TYPE_6__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_5__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct kstat {int mode; scalar_t__ size; TYPE_3__ ctime; struct timespec64 mtime; TYPE_2__ atime; scalar_t__ ino; int /*<<< orphan*/  dev; scalar_t__ blocks; int /*<<< orphan*/  rdev; scalar_t__ blksize; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; scalar_t__ nlink; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {scalar_t__ ex_uuid; scalar_t__ ex_fsid; } ;

/* Variables and functions */
#define  FSIDSOURCE_DEV 130 
#define  FSIDSOURCE_FSID 129 
#define  FSIDSOURCE_UUID 128 
 scalar_t__ NFS_MAXPATHLEN ; 
 int S_IFMT ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISLNK (int) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ from_kgid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 scalar_t__ from_kuid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int fsid_source (struct svc_fh*) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  lease_get_mtime (int /*<<< orphan*/ ,struct timespec64*) ; 
 int new_encode_dev (int /*<<< orphan*/ ) ; 
 int* nfs_ftypes ; 
 struct user_namespace* nfsd_user_namespace (struct svc_rqst*) ; 

__attribute__((used)) static __be32 *
encode_fattr(struct svc_rqst *rqstp, __be32 *p, struct svc_fh *fhp,
	     struct kstat *stat)
{
	struct user_namespace *userns = nfsd_user_namespace(rqstp);
	struct dentry	*dentry = fhp->fh_dentry;
	int type;
	struct timespec64 time;
	u32 f;

	type = (stat->mode & S_IFMT);

	*p++ = htonl(nfs_ftypes[type >> 12]);
	*p++ = htonl((u32) stat->mode);
	*p++ = htonl((u32) stat->nlink);
	*p++ = htonl((u32) from_kuid_munged(userns, stat->uid));
	*p++ = htonl((u32) from_kgid_munged(userns, stat->gid));

	if (S_ISLNK(type) && stat->size > NFS_MAXPATHLEN) {
		*p++ = htonl(NFS_MAXPATHLEN);
	} else {
		*p++ = htonl((u32) stat->size);
	}
	*p++ = htonl((u32) stat->blksize);
	if (S_ISCHR(type) || S_ISBLK(type))
		*p++ = htonl(new_encode_dev(stat->rdev));
	else
		*p++ = htonl(0xffffffff);
	*p++ = htonl((u32) stat->blocks);
	switch (fsid_source(fhp)) {
	default:
	case FSIDSOURCE_DEV:
		*p++ = htonl(new_encode_dev(stat->dev));
		break;
	case FSIDSOURCE_FSID:
		*p++ = htonl((u32) fhp->fh_export->ex_fsid);
		break;
	case FSIDSOURCE_UUID:
		f = ((u32*)fhp->fh_export->ex_uuid)[0];
		f ^= ((u32*)fhp->fh_export->ex_uuid)[1];
		f ^= ((u32*)fhp->fh_export->ex_uuid)[2];
		f ^= ((u32*)fhp->fh_export->ex_uuid)[3];
		*p++ = htonl(f);
		break;
	}
	*p++ = htonl((u32) stat->ino);
	*p++ = htonl((u32) stat->atime.tv_sec);
	*p++ = htonl(stat->atime.tv_nsec ? stat->atime.tv_nsec / 1000 : 0);
	time = stat->mtime;
	lease_get_mtime(d_inode(dentry), &time); 
	*p++ = htonl((u32) time.tv_sec);
	*p++ = htonl(time.tv_nsec ? time.tv_nsec / 1000 : 0); 
	*p++ = htonl((u32) stat->ctime.tv_sec);
	*p++ = htonl(stat->ctime.tv_nsec ? stat->ctime.tv_nsec / 1000 : 0);

	return p;
}