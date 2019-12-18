#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  attr_ver; } ;
struct TYPE_6__ {int out_pages; int page_zeroing; int page_replace; int /*<<< orphan*/  (* end ) (struct fuse_conn*,TYPE_2__*,int) ;} ;
struct fuse_args_pages {size_t num_pages; TYPE_2__ args; int /*<<< orphan*/ * pages; } ;
struct fuse_io_args {int /*<<< orphan*/  ff; TYPE_1__ read; struct fuse_args_pages ap; } ;
struct fuse_file {struct fuse_conn* fc; } ;
struct fuse_conn {scalar_t__ async_read; } ;
struct file {struct fuse_file* private_data; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_READ ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  fuse_file_get (struct fuse_file*) ; 
 int /*<<< orphan*/  fuse_get_attr_version (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_read_args_fill (struct fuse_io_args*,struct file*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_readpages_end (struct fuse_conn*,TYPE_2__*,int) ; 
 int fuse_simple_background (struct fuse_conn*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_2__*) ; 
 int /*<<< orphan*/  page_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fuse_send_readpages(struct fuse_io_args *ia, struct file *file)
{
	struct fuse_file *ff = file->private_data;
	struct fuse_conn *fc = ff->fc;
	struct fuse_args_pages *ap = &ia->ap;
	loff_t pos = page_offset(ap->pages[0]);
	size_t count = ap->num_pages << PAGE_SHIFT;
	int err;

	ap->args.out_pages = true;
	ap->args.page_zeroing = true;
	ap->args.page_replace = true;
	fuse_read_args_fill(ia, file, pos, count, FUSE_READ);
	ia->read.attr_ver = fuse_get_attr_version(fc);
	if (fc->async_read) {
		ia->ff = fuse_file_get(ff);
		ap->args.end = fuse_readpages_end;
		err = fuse_simple_background(fc, &ap->args, GFP_KERNEL);
		if (!err)
			return;
	} else {
		err = fuse_simple_request(fc, &ap->args);
	}
	fuse_readpages_end(fc, &ap->args, err);
}