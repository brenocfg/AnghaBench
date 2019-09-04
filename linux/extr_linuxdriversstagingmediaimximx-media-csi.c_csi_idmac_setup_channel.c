#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; } ;
struct TYPE_8__ {int width; int pixelformat; scalar_t__ field; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  height; } ;
struct TYPE_7__ {int width; int /*<<< orphan*/  height; } ;
struct ipu_image {TYPE_4__ pix; void* phys1; void* phys0; TYPE_3__ rect; } ;
struct TYPE_5__ {TYPE_4__ pix; } ;
struct TYPE_6__ {TYPE_1__ fmt; } ;
struct imx_media_video_dev {TYPE_2__ fmt; } ;
struct imx_media_pixfmt {int cycles; } ;
struct csi_priv {int /*<<< orphan*/  idmac_ch; int /*<<< orphan*/  smfc; int /*<<< orphan*/  upstream_ep; struct imx_media_pixfmt** cc; struct v4l2_mbus_framefmt* format_mbus; struct imx_media_video_dev* vdev; } ;
typedef  int /*<<< orphan*/  image ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 size_t CSI_SINK_PAD ; 
 scalar_t__ V4L2_FIELD_HAS_BOTH (int /*<<< orphan*/ ) ; 
 scalar_t__ V4L2_FIELD_NONE ; 
#define  V4L2_PIX_FMT_GREY 142 
#define  V4L2_PIX_FMT_NV12 141 
#define  V4L2_PIX_FMT_RGB565 140 
#define  V4L2_PIX_FMT_SBGGR16 139 
#define  V4L2_PIX_FMT_SBGGR8 138 
#define  V4L2_PIX_FMT_SGBRG16 137 
#define  V4L2_PIX_FMT_SGBRG8 136 
#define  V4L2_PIX_FMT_SGRBG16 135 
#define  V4L2_PIX_FMT_SGRBG8 134 
#define  V4L2_PIX_FMT_SRGGB16 133 
#define  V4L2_PIX_FMT_SRGGB8 132 
#define  V4L2_PIX_FMT_UYVY 131 
#define  V4L2_PIX_FMT_Y16 130 
#define  V4L2_PIX_FMT_YUV420 129 
#define  V4L2_PIX_FMT_YUYV 128 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  csi_idmac_setup_vb2_buf (struct csi_priv*,void**) ; 
 int /*<<< orphan*/  csi_idmac_unsetup_vb2_buf (struct csi_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_cpmem_interlaced_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_cpmem_set_axi_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_cpmem_set_buffer (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  ipu_cpmem_set_burstsize (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_cpmem_set_format_passthrough (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_cpmem_set_high_priority (int /*<<< orphan*/ ) ; 
 int ipu_cpmem_set_image (int /*<<< orphan*/ ,struct ipu_image*) ; 
 int /*<<< orphan*/  ipu_cpmem_set_resolution (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_cpmem_set_stride (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_cpmem_skip_odd_chroma_rows (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_cpmem_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_enable_watermark (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_idmac_set_double_buffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_smfc_set_burstsize (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_smfc_set_watermark (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (struct ipu_image*,int /*<<< orphan*/ ,int) ; 
 int requires_passthrough (int /*<<< orphan*/ *,struct v4l2_mbus_framefmt*,struct imx_media_pixfmt const*) ; 

__attribute__((used)) static int csi_idmac_setup_channel(struct csi_priv *priv)
{
	struct imx_media_video_dev *vdev = priv->vdev;
	const struct imx_media_pixfmt *incc;
	struct v4l2_mbus_framefmt *infmt;
	struct ipu_image image;
	u32 passthrough_bits;
	u32 passthrough_cycles;
	dma_addr_t phys[2];
	bool passthrough;
	u32 burst_size;
	int ret;

	infmt = &priv->format_mbus[CSI_SINK_PAD];
	incc = priv->cc[CSI_SINK_PAD];

	ipu_cpmem_zero(priv->idmac_ch);

	memset(&image, 0, sizeof(image));
	image.pix = vdev->fmt.fmt.pix;
	image.rect.width = image.pix.width;
	image.rect.height = image.pix.height;

	csi_idmac_setup_vb2_buf(priv, phys);

	image.phys0 = phys[0];
	image.phys1 = phys[1];

	passthrough = requires_passthrough(&priv->upstream_ep, infmt, incc);
	passthrough_cycles = 1;

	switch (image.pix.pixelformat) {
	case V4L2_PIX_FMT_SBGGR8:
	case V4L2_PIX_FMT_SGBRG8:
	case V4L2_PIX_FMT_SGRBG8:
	case V4L2_PIX_FMT_SRGGB8:
	case V4L2_PIX_FMT_GREY:
		burst_size = 16;
		passthrough_bits = 8;
		break;
	case V4L2_PIX_FMT_SBGGR16:
	case V4L2_PIX_FMT_SGBRG16:
	case V4L2_PIX_FMT_SGRBG16:
	case V4L2_PIX_FMT_SRGGB16:
	case V4L2_PIX_FMT_Y16:
		burst_size = 8;
		passthrough_bits = 16;
		break;
	case V4L2_PIX_FMT_YUV420:
	case V4L2_PIX_FMT_NV12:
		burst_size = (image.pix.width & 0x3f) ?
			     ((image.pix.width & 0x1f) ?
			      ((image.pix.width & 0xf) ? 8 : 16) : 32) : 64;
		passthrough_bits = 16;
		/* Skip writing U and V components to odd rows */
		ipu_cpmem_skip_odd_chroma_rows(priv->idmac_ch);
		break;
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_UYVY:
		burst_size = (image.pix.width & 0x1f) ?
			     ((image.pix.width & 0xf) ? 8 : 16) : 32;
		passthrough_bits = 16;
		break;
	case V4L2_PIX_FMT_RGB565:
		if (passthrough) {
			burst_size = 16;
			passthrough_bits = 8;
			passthrough_cycles = incc->cycles;
			break;
		}
		/* fallthrough - non-passthrough RGB565 (CSI-2 bus) */
	default:
		burst_size = (image.pix.width & 0xf) ? 8 : 16;
		passthrough_bits = 16;
		break;
	}

	if (passthrough) {
		ipu_cpmem_set_resolution(priv->idmac_ch,
					 image.rect.width * passthrough_cycles,
					 image.rect.height);
		ipu_cpmem_set_stride(priv->idmac_ch, image.pix.bytesperline);
		ipu_cpmem_set_buffer(priv->idmac_ch, 0, image.phys0);
		ipu_cpmem_set_buffer(priv->idmac_ch, 1, image.phys1);
		ipu_cpmem_set_format_passthrough(priv->idmac_ch,
						 passthrough_bits);
	} else {
		ret = ipu_cpmem_set_image(priv->idmac_ch, &image);
		if (ret)
			goto unsetup_vb2;
	}

	ipu_cpmem_set_burstsize(priv->idmac_ch, burst_size);

	/*
	 * Set the channel for the direct CSI-->memory via SMFC
	 * use-case to very high priority, by enabling the watermark
	 * signal in the SMFC, enabling WM in the channel, and setting
	 * the channel priority to high.
	 *
	 * Refer to the i.mx6 rev. D TRM Table 36-8: Calculated priority
	 * value.
	 *
	 * The WM's are set very low by intention here to ensure that
	 * the SMFC FIFOs do not overflow.
	 */
	ipu_smfc_set_watermark(priv->smfc, 0x02, 0x01);
	ipu_cpmem_set_high_priority(priv->idmac_ch);
	ipu_idmac_enable_watermark(priv->idmac_ch, true);
	ipu_cpmem_set_axi_id(priv->idmac_ch, 0);

	burst_size = passthrough ?
		(burst_size >> 3) - 1 : (burst_size >> 2) - 1;

	ipu_smfc_set_burstsize(priv->smfc, burst_size);

	if (image.pix.field == V4L2_FIELD_NONE &&
	    V4L2_FIELD_HAS_BOTH(infmt->field))
		ipu_cpmem_interlaced_scan(priv->idmac_ch,
					  image.pix.bytesperline);

	ipu_idmac_set_double_buffer(priv->idmac_ch, true);

	return 0;

unsetup_vb2:
	csi_idmac_unsetup_vb2_buf(priv, VB2_BUF_STATE_QUEUED);
	return ret;
}