#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct fuse_conn {int dummy; } ;
struct TYPE_10__ {int in_numargs; int out_numargs; int out_argvar; int out_pages; int /*<<< orphan*/  end; TYPE_4__* out_args; TYPE_1__* in_args; int /*<<< orphan*/  opcode; } ;
struct fuse_args_pages {int num_pages; TYPE_5__ args; TYPE_3__* descs; struct page** pages; } ;
struct TYPE_8__ {int length; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct cuse_init_args {TYPE_3__ desc; struct page* page; int /*<<< orphan*/  out; TYPE_2__ in; struct fuse_args_pages ap; } ;
struct cuse_conn {struct fuse_conn fc; } ;
struct TYPE_9__ {int size; int /*<<< orphan*/ * value; } ;
struct TYPE_6__ {int size; TYPE_2__* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CUSE_INIT ; 
 int CUSE_INIT_INFO_MAX ; 
 int /*<<< orphan*/  CUSE_UNRESTRICTED_IOCTL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FUSE_KERNEL_MINOR_VERSION ; 
 int /*<<< orphan*/  FUSE_KERNEL_VERSION ; 
 int GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  cuse_process_init_reply ; 
 int fuse_simple_background (struct fuse_conn*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  kfree (struct cuse_init_args*) ; 
 struct cuse_init_args* kzalloc (int,int) ; 

__attribute__((used)) static int cuse_send_init(struct cuse_conn *cc)
{
	int rc;
	struct page *page;
	struct fuse_conn *fc = &cc->fc;
	struct cuse_init_args *ia;
	struct fuse_args_pages *ap;

	BUILD_BUG_ON(CUSE_INIT_INFO_MAX > PAGE_SIZE);

	rc = -ENOMEM;
	page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	if (!page)
		goto err;

	ia = kzalloc(sizeof(*ia), GFP_KERNEL);
	if (!ia)
		goto err_free_page;

	ap = &ia->ap;
	ia->in.major = FUSE_KERNEL_VERSION;
	ia->in.minor = FUSE_KERNEL_MINOR_VERSION;
	ia->in.flags |= CUSE_UNRESTRICTED_IOCTL;
	ap->args.opcode = CUSE_INIT;
	ap->args.in_numargs = 1;
	ap->args.in_args[0].size = sizeof(ia->in);
	ap->args.in_args[0].value = &ia->in;
	ap->args.out_numargs = 2;
	ap->args.out_args[0].size = sizeof(ia->out);
	ap->args.out_args[0].value = &ia->out;
	ap->args.out_args[1].size = CUSE_INIT_INFO_MAX;
	ap->args.out_argvar = 1;
	ap->args.out_pages = 1;
	ap->num_pages = 1;
	ap->pages = &ia->page;
	ap->descs = &ia->desc;
	ia->page = page;
	ia->desc.length = ap->args.out_args[1].size;
	ap->args.end = cuse_process_init_reply;

	rc = fuse_simple_background(fc, &ap->args, GFP_KERNEL);
	if (rc) {
		kfree(ia);
err_free_page:
		__free_page(page);
	}
err:
	return rc;
}