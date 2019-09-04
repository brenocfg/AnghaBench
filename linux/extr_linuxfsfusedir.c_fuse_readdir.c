#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_7__ {int error; } ;
struct TYPE_8__ {int argpages; TYPE_3__ h; TYPE_2__* args; } ;
struct fuse_req {int num_pages; TYPE_4__ out; TYPE_1__* page_descs; struct page** pages; } ;
struct fuse_conn {int dummy; } ;
struct file {int dummy; } ;
struct dir_context {int /*<<< orphan*/  pos; } ;
struct TYPE_6__ {size_t size; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FUSE_READDIR ; 
 int /*<<< orphan*/  FUSE_READDIRPLUS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct fuse_req*) ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  fuse_get_attr_version (struct fuse_conn*) ; 
 struct fuse_req* fuse_get_req (struct fuse_conn*,int) ; 
 int /*<<< orphan*/  fuse_invalidate_atime (struct inode*) ; 
 int fuse_lock_inode (struct inode*) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_read_fill (struct fuse_req*,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_unlock_inode (struct inode*,int) ; 
 int fuse_use_readdirplus (struct inode*,struct dir_context*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int parse_dirfile (int /*<<< orphan*/ ,size_t,struct file*,struct dir_context*) ; 
 int parse_dirplusfile (int /*<<< orphan*/ ,size_t,struct file*,struct dir_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fuse_readdir(struct file *file, struct dir_context *ctx)
{
	int plus, err;
	size_t nbytes;
	struct page *page;
	struct inode *inode = file_inode(file);
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_req *req;
	u64 attr_version = 0;
	bool locked;

	if (is_bad_inode(inode))
		return -EIO;

	req = fuse_get_req(fc, 1);
	if (IS_ERR(req))
		return PTR_ERR(req);

	page = alloc_page(GFP_KERNEL);
	if (!page) {
		fuse_put_request(fc, req);
		return -ENOMEM;
	}

	plus = fuse_use_readdirplus(inode, ctx);
	req->out.argpages = 1;
	req->num_pages = 1;
	req->pages[0] = page;
	req->page_descs[0].length = PAGE_SIZE;
	if (plus) {
		attr_version = fuse_get_attr_version(fc);
		fuse_read_fill(req, file, ctx->pos, PAGE_SIZE,
			       FUSE_READDIRPLUS);
	} else {
		fuse_read_fill(req, file, ctx->pos, PAGE_SIZE,
			       FUSE_READDIR);
	}
	locked = fuse_lock_inode(inode);
	fuse_request_send(fc, req);
	fuse_unlock_inode(inode, locked);
	nbytes = req->out.args[0].size;
	err = req->out.h.error;
	fuse_put_request(fc, req);
	if (!err) {
		if (plus) {
			err = parse_dirplusfile(page_address(page), nbytes,
						file, ctx,
						attr_version);
		} else {
			err = parse_dirfile(page_address(page), nbytes, file,
					    ctx);
		}
	}

	__free_page(page);
	fuse_invalidate_atime(inode);
	return err;
}