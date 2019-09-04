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
typedef  int u32 ;
struct bcm2835_codec_ctx {void* quant; int /*<<< orphan*/  ycbcr_enc; void* xfer_func; void* colorspace; } ;

/* Variables and functions */
#define  MMAL_COLOR_SPACE_ITUR_BT601 129 
#define  MMAL_COLOR_SPACE_ITUR_BT709 128 
 void* V4L2_COLORSPACE_REC709 ; 
 void* V4L2_QUANTIZATION_LIM_RANGE ; 
 void* V4L2_XFER_FUNC_709 ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_601 ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_709 ; 

__attribute__((used)) static void color_mmal2v4l(struct bcm2835_codec_ctx *ctx, u32 mmal_color_space)
{
	switch (mmal_color_space) {
	case MMAL_COLOR_SPACE_ITUR_BT601:
		ctx->colorspace = V4L2_COLORSPACE_REC709;
		ctx->xfer_func = V4L2_XFER_FUNC_709;
		ctx->ycbcr_enc = V4L2_YCBCR_ENC_601;
		ctx->quant = V4L2_QUANTIZATION_LIM_RANGE;
		break;

	case MMAL_COLOR_SPACE_ITUR_BT709:
		ctx->colorspace = V4L2_COLORSPACE_REC709;
		ctx->xfer_func = V4L2_XFER_FUNC_709;
		ctx->ycbcr_enc = V4L2_YCBCR_ENC_709;
		ctx->quant = V4L2_QUANTIZATION_LIM_RANGE;
		break;
	}
}