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
struct svc_fh {int /*<<< orphan*/  fh_dentry; TYPE_2__* fh_export; } ;
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;
struct kstat {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  mnt; } ;
struct TYPE_4__ {TYPE_1__ ex_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_STATX_SYNC_AS_STAT ; 
 int /*<<< orphan*/  STATX_BASIC_STATS ; 
 int /*<<< orphan*/  nfserrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_getattr (struct path*,struct kstat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __be32 fh_getattr(struct svc_fh *fh, struct kstat *stat)
{
	struct path p = {.mnt = fh->fh_export->ex_path.mnt,
			 .dentry = fh->fh_dentry};
	return nfserrno(vfs_getattr(&p, stat, STATX_BASIC_STATS,
				    AT_STATX_SYNC_AS_STAT));
}