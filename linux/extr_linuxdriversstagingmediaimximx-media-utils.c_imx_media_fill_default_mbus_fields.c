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
struct v4l2_mbus_framefmt {scalar_t__ field; scalar_t__ xfer_func; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  quantization; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; } ;
struct imx_media_pixfmt {scalar_t__ cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SEL_ANY ; 
 scalar_t__ IPUV3_COLORSPACE_YUV ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_DEFAULT ; 
 scalar_t__ V4L2_FIELD_ANY ; 
 int /*<<< orphan*/  V4L2_MAP_QUANTIZATION_DEFAULT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ V4L2_MAP_XFER_FUNC_DEFAULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_MAP_YCBCR_ENC_DEFAULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_FULL_RANGE ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_LIM_RANGE ; 
 scalar_t__ V4L2_XFER_FUNC_DEFAULT ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_601 ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 
 struct imx_media_pixfmt* imx_media_find_ipu_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct imx_media_pixfmt* imx_media_find_mbus_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void imx_media_fill_default_mbus_fields(struct v4l2_mbus_framefmt *tryfmt,
					struct v4l2_mbus_framefmt *fmt,
					bool ic_route)
{
	const struct imx_media_pixfmt *cc;
	bool is_rgb = false;

	cc = imx_media_find_mbus_format(tryfmt->code, CS_SEL_ANY, true);
	if (!cc)
		cc = imx_media_find_ipu_format(tryfmt->code, CS_SEL_ANY);
	if (cc && cc->cs != IPUV3_COLORSPACE_YUV)
		is_rgb = true;

	/* fill field if necessary */
	if (tryfmt->field == V4L2_FIELD_ANY)
		tryfmt->field = fmt->field;

	/* fill colorimetry if necessary */
	if (tryfmt->colorspace == V4L2_COLORSPACE_DEFAULT) {
		tryfmt->colorspace = fmt->colorspace;
		tryfmt->xfer_func = fmt->xfer_func;
		tryfmt->ycbcr_enc = fmt->ycbcr_enc;
		tryfmt->quantization = fmt->quantization;
	} else {
		if (tryfmt->xfer_func == V4L2_XFER_FUNC_DEFAULT) {
			tryfmt->xfer_func =
				V4L2_MAP_XFER_FUNC_DEFAULT(tryfmt->colorspace);
		}
		if (tryfmt->ycbcr_enc == V4L2_YCBCR_ENC_DEFAULT) {
			tryfmt->ycbcr_enc =
				V4L2_MAP_YCBCR_ENC_DEFAULT(tryfmt->colorspace);
		}
		if (tryfmt->quantization == V4L2_QUANTIZATION_DEFAULT) {
			tryfmt->quantization =
				V4L2_MAP_QUANTIZATION_DEFAULT(
					is_rgb, tryfmt->colorspace,
					tryfmt->ycbcr_enc);
		}
	}

	if (ic_route) {
		tryfmt->quantization = is_rgb ?
			V4L2_QUANTIZATION_FULL_RANGE :
			V4L2_QUANTIZATION_LIM_RANGE;
		tryfmt->ycbcr_enc = V4L2_YCBCR_ENC_601;
	}
}