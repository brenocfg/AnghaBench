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
struct v4l2_subdev {int dummy; } ;
struct csi_priv {scalar_t__ csi; scalar_t__ fim; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx_media_capture_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_fim_free (scalar_t__) ; 
 int /*<<< orphan*/  ipu_csi_put (scalar_t__) ; 
 struct csi_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static void csi_unregistered(struct v4l2_subdev *sd)
{
	struct csi_priv *priv = v4l2_get_subdevdata(sd);

	imx_media_capture_device_unregister(priv->vdev);

	if (priv->fim)
		imx_media_fim_free(priv->fim);

	if (priv->csi)
		ipu_csi_put(priv->csi);
}