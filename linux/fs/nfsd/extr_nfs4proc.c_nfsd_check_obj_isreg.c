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
typedef  int /*<<< orphan*/  umode_t ;
struct svc_fh {int /*<<< orphan*/  fh_dentry; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 TYPE_1__* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_isdir ; 
 int /*<<< orphan*/  nfserr_symlink ; 

__attribute__((used)) static __be32 nfsd_check_obj_isreg(struct svc_fh *fh)
{
	umode_t mode = d_inode(fh->fh_dentry)->i_mode;

	if (S_ISREG(mode))
		return nfs_ok;
	if (S_ISDIR(mode))
		return nfserr_isdir;
	/*
	 * Using err_symlink as our catch-all case may look odd; but
	 * there's no other obvious error for this case in 4.0, and we
	 * happen to know that it will cause the linux v4 client to do
	 * the right thing on attempts to open something other than a
	 * regular file.
	 */
	return nfserr_symlink;
}