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
struct csi_priv {scalar_t__ dest; scalar_t__ fim; int /*<<< orphan*/  src_sd; int /*<<< orphan*/  csi; } ;

/* Variables and functions */
 scalar_t__ IPU_CSI_DEST_IDMAC ; 
 int /*<<< orphan*/  csi_idmac_stop (struct csi_priv*) ; 
 int /*<<< orphan*/  csi_idmac_wait_last_eof (struct csi_priv*) ; 
 int /*<<< orphan*/  imx_media_fim_set_stream (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ipu_csi_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static void csi_stop(struct csi_priv *priv)
{
	if (priv->dest == IPU_CSI_DEST_IDMAC)
		csi_idmac_wait_last_eof(priv);

	/*
	 * Disable the CSI asap, after syncing with the last EOF.
	 * Doing so after the IDMA channel is disabled has shown to
	 * create hard system-wide hangs.
	 */
	ipu_csi_disable(priv->csi);

	/* stop upstream */
	v4l2_subdev_call(priv->src_sd, video, s_stream, 0);

	if (priv->dest == IPU_CSI_DEST_IDMAC) {
		csi_idmac_stop(priv);

		/* stop the frame interval monitor */
		if (priv->fim)
			imx_media_fim_set_stream(priv->fim, NULL, false);
	}
}