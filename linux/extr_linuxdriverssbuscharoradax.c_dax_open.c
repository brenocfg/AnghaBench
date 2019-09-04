#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {int dummy; } ;
struct file {struct dax_ctx* private_data; } ;
struct dax_ctx {struct dax_ctx* ccb_buf; int /*<<< orphan*/  owner; void* ca_buf_ra; struct dax_ctx* ca_buf; int /*<<< orphan*/  status; void* ccb_buf_ra; } ;
struct dax_ccb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCA_STAT_COMPLETED ; 
 int DAX_CA_ELEMS ; 
 int /*<<< orphan*/  DAX_MAX_CCBS ; 
 int DAX_MMAP_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dax_dbg (char*,void*,void*,...) ; 
 struct dax_ctx* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dax_ctx*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* virt_to_phys (struct dax_ctx*) ; 

__attribute__((used)) static int dax_open(struct inode *inode, struct file *f)
{
	struct dax_ctx *ctx = NULL;
	int i;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (ctx == NULL)
		goto done;

	ctx->ccb_buf = kcalloc(DAX_MAX_CCBS, sizeof(struct dax_ccb),
			       GFP_KERNEL);
	if (ctx->ccb_buf == NULL)
		goto done;

	ctx->ccb_buf_ra = virt_to_phys(ctx->ccb_buf);
	dax_dbg("ctx->ccb_buf=0x%p, ccb_buf_ra=0x%llx",
		(void *)ctx->ccb_buf, ctx->ccb_buf_ra);

	/* allocate CCB completion area buffer */
	ctx->ca_buf = kzalloc(DAX_MMAP_LEN, GFP_KERNEL);
	if (ctx->ca_buf == NULL)
		goto alloc_error;
	for (i = 0; i < DAX_CA_ELEMS; i++)
		ctx->ca_buf[i].status = CCA_STAT_COMPLETED;

	ctx->ca_buf_ra = virt_to_phys(ctx->ca_buf);
	dax_dbg("ctx=0x%p, ctx->ca_buf=0x%p, ca_buf_ra=0x%llx",
		(void *)ctx, (void *)ctx->ca_buf, ctx->ca_buf_ra);

	ctx->owner = current;
	f->private_data = ctx;
	return 0;

alloc_error:
	kfree(ctx->ccb_buf);
done:
	kfree(ctx);
	return -ENOMEM;
}