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
struct gntdev_dmabuf_wait_obj {int dummy; } ;
struct gntdev_dmabuf_priv {int dummy; } ;
typedef  struct gntdev_dmabuf_wait_obj gntdev_dmabuf ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct gntdev_dmabuf_wait_obj*) ; 
 int PTR_ERR (struct gntdev_dmabuf_wait_obj*) ; 
 int /*<<< orphan*/  dmabuf_exp_wait_obj_free (struct gntdev_dmabuf_priv*,struct gntdev_dmabuf_wait_obj*) ; 
 struct gntdev_dmabuf_wait_obj* dmabuf_exp_wait_obj_get_dmabuf (struct gntdev_dmabuf_priv*,int) ; 
 struct gntdev_dmabuf_wait_obj* dmabuf_exp_wait_obj_new (struct gntdev_dmabuf_priv*,struct gntdev_dmabuf_wait_obj*) ; 
 int dmabuf_exp_wait_obj_wait (struct gntdev_dmabuf_wait_obj*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int dmabuf_exp_wait_released(struct gntdev_dmabuf_priv *priv, int fd,
				    int wait_to_ms)
{
	struct gntdev_dmabuf *gntdev_dmabuf;
	struct gntdev_dmabuf_wait_obj *obj;
	int ret;

	pr_debug("Will wait for dma-buf with fd %d\n", fd);
	/*
	 * Try to find the DMA buffer: if not found means that
	 * either the buffer has already been released or file descriptor
	 * provided is wrong.
	 */
	gntdev_dmabuf = dmabuf_exp_wait_obj_get_dmabuf(priv, fd);
	if (IS_ERR(gntdev_dmabuf))
		return PTR_ERR(gntdev_dmabuf);

	/*
	 * gntdev_dmabuf still exists and is reference count locked by us now,
	 * so prepare to wait: allocate wait object and add it to the wait list,
	 * so we can find it on release.
	 */
	obj = dmabuf_exp_wait_obj_new(priv, gntdev_dmabuf);
	if (IS_ERR(obj))
		return PTR_ERR(obj);

	ret = dmabuf_exp_wait_obj_wait(obj, wait_to_ms);
	dmabuf_exp_wait_obj_free(priv, obj);
	return ret;
}