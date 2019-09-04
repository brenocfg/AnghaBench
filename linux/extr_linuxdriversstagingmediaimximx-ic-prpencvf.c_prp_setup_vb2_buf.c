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
struct TYPE_4__ {int /*<<< orphan*/  phys; } ;
struct prp_priv {TYPE_2__ underrun_buf; struct imx_media_buffer** active_vb2_buf; struct imx_media_video_dev* vdev; } ;
struct imx_media_video_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  vb2_buf; } ;
struct imx_media_buffer {TYPE_1__ vbuf; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 struct imx_media_buffer* imx_media_capture_device_next_buf (struct imx_media_video_dev*) ; 
 int /*<<< orphan*/  vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prp_setup_vb2_buf(struct prp_priv *priv, dma_addr_t *phys)
{
	struct imx_media_video_dev *vdev = priv->vdev;
	struct imx_media_buffer *buf;
	int i;

	for (i = 0; i < 2; i++) {
		buf = imx_media_capture_device_next_buf(vdev);
		if (buf) {
			priv->active_vb2_buf[i] = buf;
			phys[i] = vb2_dma_contig_plane_dma_addr(
				&buf->vbuf.vb2_buf, 0);
		} else {
			priv->active_vb2_buf[i] = NULL;
			phys[i] = priv->underrun_buf.phys;
		}
	}
}