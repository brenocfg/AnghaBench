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
struct gntdev_dmabuf_priv {struct file* filp; int /*<<< orphan*/  imp_list; int /*<<< orphan*/  exp_wait_list; int /*<<< orphan*/  exp_list; int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct gntdev_dmabuf_priv* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct gntdev_dmabuf_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct gntdev_dmabuf_priv *gntdev_dmabuf_init(struct file *filp)
{
	struct gntdev_dmabuf_priv *priv;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return ERR_PTR(-ENOMEM);

	mutex_init(&priv->lock);
	INIT_LIST_HEAD(&priv->exp_list);
	INIT_LIST_HEAD(&priv->exp_wait_list);
	INIT_LIST_HEAD(&priv->imp_list);

	priv->filp = filp;

	return priv;
}