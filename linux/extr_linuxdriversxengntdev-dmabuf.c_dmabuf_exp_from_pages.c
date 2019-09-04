#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct gntdev_dmabuf_export_args {int count; int fd; TYPE_5__* dmabuf_priv; TYPE_4__* dev; int /*<<< orphan*/  map; int /*<<< orphan*/  priv; int /*<<< orphan*/  pages; } ;
struct TYPE_9__ {int /*<<< orphan*/  map; int /*<<< orphan*/  priv; int /*<<< orphan*/  refcount; } ;
struct TYPE_10__ {TYPE_1__ exp; } ;
struct gntdev_dmabuf {int nr_pages; int fd; int /*<<< orphan*/ * dmabuf; TYPE_5__* priv; int /*<<< orphan*/  next; TYPE_2__ u; int /*<<< orphan*/  pages; } ;
struct TYPE_14__ {int size; struct gntdev_dmabuf* priv; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; scalar_t__ owner; int /*<<< orphan*/  exp_name; } ;
struct TYPE_13__ {int /*<<< orphan*/  filp; int /*<<< orphan*/  lock; int /*<<< orphan*/  exp_list; } ;
struct TYPE_12__ {TYPE_3__* driver; } ;
struct TYPE_11__ {scalar_t__ owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_DMA_BUF_EXPORT_INFO (TYPE_6__) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ THIS_MODULE ; 
 int /*<<< orphan*/ * dma_buf_export (TYPE_6__*) ; 
 int dma_buf_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmabuf_exp_ops ; 
 TYPE_6__ exp_info ; 
 int /*<<< orphan*/  get_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gntdev_dmabuf*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct gntdev_dmabuf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int dmabuf_exp_from_pages(struct gntdev_dmabuf_export_args *args)
{
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);
	struct gntdev_dmabuf *gntdev_dmabuf;
	int ret;

	gntdev_dmabuf = kzalloc(sizeof(*gntdev_dmabuf), GFP_KERNEL);
	if (!gntdev_dmabuf)
		return -ENOMEM;

	kref_init(&gntdev_dmabuf->u.exp.refcount);

	gntdev_dmabuf->priv = args->dmabuf_priv;
	gntdev_dmabuf->nr_pages = args->count;
	gntdev_dmabuf->pages = args->pages;
	gntdev_dmabuf->u.exp.priv = args->priv;
	gntdev_dmabuf->u.exp.map = args->map;

	exp_info.exp_name = KBUILD_MODNAME;
	if (args->dev->driver && args->dev->driver->owner)
		exp_info.owner = args->dev->driver->owner;
	else
		exp_info.owner = THIS_MODULE;
	exp_info.ops = &dmabuf_exp_ops;
	exp_info.size = args->count << PAGE_SHIFT;
	exp_info.flags = O_RDWR;
	exp_info.priv = gntdev_dmabuf;

	gntdev_dmabuf->dmabuf = dma_buf_export(&exp_info);
	if (IS_ERR(gntdev_dmabuf->dmabuf)) {
		ret = PTR_ERR(gntdev_dmabuf->dmabuf);
		gntdev_dmabuf->dmabuf = NULL;
		goto fail;
	}

	ret = dma_buf_fd(gntdev_dmabuf->dmabuf, O_CLOEXEC);
	if (ret < 0)
		goto fail;

	gntdev_dmabuf->fd = ret;
	args->fd = ret;

	pr_debug("Exporting DMA buffer with fd %d\n", ret);

	mutex_lock(&args->dmabuf_priv->lock);
	list_add(&gntdev_dmabuf->next, &args->dmabuf_priv->exp_list);
	mutex_unlock(&args->dmabuf_priv->lock);
	get_file(gntdev_dmabuf->priv->filp);
	return 0;

fail:
	if (gntdev_dmabuf->dmabuf)
		dma_buf_put(gntdev_dmabuf->dmabuf);
	kfree(gntdev_dmabuf);
	return ret;
}