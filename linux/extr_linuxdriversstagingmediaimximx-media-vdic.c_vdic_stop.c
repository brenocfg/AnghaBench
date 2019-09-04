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
struct vdic_priv {TYPE_1__* ops; int /*<<< orphan*/  vdi; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct vdic_priv*) ;int /*<<< orphan*/  (* stop ) (struct vdic_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_vdi_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct vdic_priv*) ; 
 int /*<<< orphan*/  stub2 (struct vdic_priv*) ; 
 int /*<<< orphan*/  vdic_put_ipu_resources (struct vdic_priv*) ; 

__attribute__((used)) static void vdic_stop(struct vdic_priv *priv)
{
	priv->ops->stop(priv);
	ipu_vdi_disable(priv->vdi);
	priv->ops->disable(priv);

	vdic_put_ipu_resources(priv);
}