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
struct prp_priv {int /*<<< orphan*/  csi_id; int /*<<< orphan*/  ipu; TYPE_2__* src_sd; TYPE_1__* md; struct imx_ic_priv* ic_priv; } ;
struct imx_ic_priv {size_t ipu_id; } ;
struct TYPE_4__ {int grp_id; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ipu; } ;

/* Variables and functions */
 int IMX_MEDIA_GRP_ID_VDIC ; 
 int /*<<< orphan*/  ipu_set_ic_src_mux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int prp_start(struct prp_priv *priv)
{
	struct imx_ic_priv *ic_priv = priv->ic_priv;
	bool src_is_vdic;

	priv->ipu = priv->md->ipu[ic_priv->ipu_id];

	/* set IC to receive from CSI or VDI depending on source */
	src_is_vdic = !!(priv->src_sd->grp_id & IMX_MEDIA_GRP_ID_VDIC);

	ipu_set_ic_src_mux(priv->ipu, priv->csi_id, src_is_vdic);

	return 0;
}