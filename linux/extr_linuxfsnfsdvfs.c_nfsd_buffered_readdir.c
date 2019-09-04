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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  actor; } ;
struct readdir_data {void* dirent; int used; scalar_t__ full; TYPE_1__ ctx; } ;
struct readdir_cd {scalar_t__ err; } ;
struct file {int dummy; } ;
struct buffered_dirent {scalar_t__ namlen; int /*<<< orphan*/  d_type; int /*<<< orphan*/  ino; int /*<<< orphan*/  offset; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ (* nfsd_filldir_t ) (struct readdir_cd*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 unsigned int ALIGN (scalar_t__,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int iterate_dir (struct file*,TYPE_1__*) ; 
 scalar_t__ nfs_ok ; 
 int /*<<< orphan*/  nfsd_buffered_filldir ; 
 scalar_t__ nfserr_eof ; 
 scalar_t__ nfserrno (int) ; 
 int /*<<< orphan*/  vfs_llseek (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 nfsd_buffered_readdir(struct file *file, nfsd_filldir_t func,
				    struct readdir_cd *cdp, loff_t *offsetp)
{
	struct buffered_dirent *de;
	int host_err;
	int size;
	loff_t offset;
	struct readdir_data buf = {
		.ctx.actor = nfsd_buffered_filldir,
		.dirent = (void *)__get_free_page(GFP_KERNEL)
	};

	if (!buf.dirent)
		return nfserrno(-ENOMEM);

	offset = *offsetp;

	while (1) {
		unsigned int reclen;

		cdp->err = nfserr_eof; /* will be cleared on successful read */
		buf.used = 0;
		buf.full = 0;

		host_err = iterate_dir(file, &buf.ctx);
		if (buf.full)
			host_err = 0;

		if (host_err < 0)
			break;

		size = buf.used;

		if (!size)
			break;

		de = (struct buffered_dirent *)buf.dirent;
		while (size > 0) {
			offset = de->offset;

			if (func(cdp, de->name, de->namlen, de->offset,
				 de->ino, de->d_type))
				break;

			if (cdp->err != nfs_ok)
				break;

			reclen = ALIGN(sizeof(*de) + de->namlen,
				       sizeof(u64));
			size -= reclen;
			de = (struct buffered_dirent *)((char *)de + reclen);
		}
		if (size > 0) /* We bailed out early */
			break;

		offset = vfs_llseek(file, 0, SEEK_CUR);
	}

	free_page((unsigned long)(buf.dirent));

	if (host_err)
		return nfserrno(host_err);

	*offsetp = offset;
	return cdp->err;
}