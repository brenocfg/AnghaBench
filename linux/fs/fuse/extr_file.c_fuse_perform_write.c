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
struct kiocb {int dummy; } ;
struct iov_iter {int dummy; } ;
struct inode {scalar_t__ i_size; } ;
struct TYPE_3__ {size_t size; } ;
struct TYPE_4__ {TYPE_1__ out; } ;
struct fuse_args_pages {int /*<<< orphan*/  pages; int /*<<< orphan*/  descs; } ;
struct fuse_io_args {TYPE_2__ write; struct fuse_args_pages ap; } ;
struct fuse_inode {int /*<<< orphan*/  state; } ;
struct fuse_conn {int /*<<< orphan*/  max_pages; } ;
struct address_space {struct inode* host; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FUSE_I_SIZE_UNSTABLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t fuse_fill_write_pages (struct fuse_args_pages*,struct address_space*,struct iov_iter*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  fuse_pages_alloc (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fuse_send_write_pages (struct fuse_io_args*,struct kiocb*,struct inode*,scalar_t__,size_t) ; 
 unsigned int fuse_wr_pages (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_write_update_size (struct inode*,scalar_t__) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 scalar_t__ iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t fuse_perform_write(struct kiocb *iocb,
				  struct address_space *mapping,
				  struct iov_iter *ii, loff_t pos)
{
	struct inode *inode = mapping->host;
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_inode *fi = get_fuse_inode(inode);
	int err = 0;
	ssize_t res = 0;

	if (inode->i_size < pos + iov_iter_count(ii))
		set_bit(FUSE_I_SIZE_UNSTABLE, &fi->state);

	do {
		ssize_t count;
		struct fuse_io_args ia = {};
		struct fuse_args_pages *ap = &ia.ap;
		unsigned int nr_pages = fuse_wr_pages(pos, iov_iter_count(ii),
						      fc->max_pages);

		ap->pages = fuse_pages_alloc(nr_pages, GFP_KERNEL, &ap->descs);
		if (!ap->pages) {
			err = -ENOMEM;
			break;
		}

		count = fuse_fill_write_pages(ap, mapping, ii, pos, nr_pages);
		if (count <= 0) {
			err = count;
		} else {
			err = fuse_send_write_pages(&ia, iocb, inode,
						    pos, count);
			if (!err) {
				size_t num_written = ia.write.out.size;

				res += num_written;
				pos += num_written;

				/* break out of the loop on short write */
				if (num_written != count)
					err = -EIO;
			}
		}
		kfree(ap->pages);
	} while (!err && iov_iter_count(ii));

	if (res > 0)
		fuse_write_update_size(inode, pos);

	clear_bit(FUSE_I_SIZE_UNSTABLE, &fi->state);
	fuse_invalidate_attr(inode);

	return res > 0 ? res : err;
}