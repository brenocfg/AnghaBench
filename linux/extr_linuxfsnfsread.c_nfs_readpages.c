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
struct nfs_readdesc {int /*<<< orphan*/ * ctx; struct nfs_pageio_descriptor* pgio; } ;
struct nfs_pgio_mirror {int pg_bytes_written; } ;
struct nfs_pageio_descriptor {int pg_mirror_count; struct nfs_pgio_mirror* pg_mirrors; } ;
struct list_head {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
struct TYPE_4__ {int read_io; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int EBADF ; 
 int ESTALE ; 
 int /*<<< orphan*/  FMODE_READ ; 
 int /*<<< orphan*/  NFSIOS_READPAGES ; 
 int /*<<< orphan*/  NFSIOS_VFSREADPAGES ; 
 scalar_t__ NFS_FILEID (struct inode*) ; 
 TYPE_2__* NFS_I (struct inode*) ; 
 scalar_t__ NFS_STALE (struct inode*) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned long long,unsigned int) ; 
 int /*<<< orphan*/ * get_nfs_open_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_add_stats (struct inode*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  nfs_async_read_completion_ops ; 
 int /*<<< orphan*/  nfs_file_open_context (struct file*) ; 
 int /*<<< orphan*/ * nfs_find_open_context (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pageio_complete (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_pageio_init_read (struct nfs_pageio_descriptor*,struct inode*,int,int /*<<< orphan*/ *) ; 
 int nfs_readpages_from_fscache (int /*<<< orphan*/ *,struct inode*,struct address_space*,struct list_head*,unsigned int*) ; 
 int /*<<< orphan*/  put_nfs_open_context (int /*<<< orphan*/ *) ; 
 int read_cache_pages (struct address_space*,struct list_head*,int /*<<< orphan*/ ,struct nfs_readdesc*) ; 
 int /*<<< orphan*/  readpage_async_filler ; 

int nfs_readpages(struct file *filp, struct address_space *mapping,
		struct list_head *pages, unsigned nr_pages)
{
	struct nfs_pageio_descriptor pgio;
	struct nfs_pgio_mirror *pgm;
	struct nfs_readdesc desc = {
		.pgio = &pgio,
	};
	struct inode *inode = mapping->host;
	unsigned long npages;
	int ret = -ESTALE;

	dprintk("NFS: nfs_readpages (%s/%Lu %d)\n",
			inode->i_sb->s_id,
			(unsigned long long)NFS_FILEID(inode),
			nr_pages);
	nfs_inc_stats(inode, NFSIOS_VFSREADPAGES);

	if (NFS_STALE(inode))
		goto out;

	if (filp == NULL) {
		desc.ctx = nfs_find_open_context(inode, NULL, FMODE_READ);
		if (desc.ctx == NULL)
			return -EBADF;
	} else
		desc.ctx = get_nfs_open_context(nfs_file_open_context(filp));

	/* attempt to read as many of the pages as possible from the cache
	 * - this returns -ENOBUFS immediately if the cookie is negative
	 */
	ret = nfs_readpages_from_fscache(desc.ctx, inode, mapping,
					 pages, &nr_pages);
	if (ret == 0)
		goto read_complete; /* all pages were read */

	nfs_pageio_init_read(&pgio, inode, false,
			     &nfs_async_read_completion_ops);

	ret = read_cache_pages(mapping, pages, readpage_async_filler, &desc);
	nfs_pageio_complete(&pgio);

	/* It doesn't make sense to do mirrored reads! */
	WARN_ON_ONCE(pgio.pg_mirror_count != 1);

	pgm = &pgio.pg_mirrors[0];
	NFS_I(inode)->read_io += pgm->pg_bytes_written;
	npages = (pgm->pg_bytes_written + PAGE_SIZE - 1) >>
		 PAGE_SHIFT;
	nfs_add_stats(inode, NFSIOS_READPAGES, npages);
read_complete:
	put_nfs_open_context(desc.ctx);
out:
	return ret;
}