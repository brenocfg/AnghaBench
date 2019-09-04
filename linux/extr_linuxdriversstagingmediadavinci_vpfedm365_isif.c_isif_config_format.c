#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct vpfe_isif_device {TYPE_2__* formats; TYPE_1__ crop; } ;
struct vpfe_device {struct vpfe_isif_device vpfe_isif; int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_pix_format {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
typedef  enum isif_frmfmt { ____Placeholder_isif_frmfmt } isif_frmfmt ;
struct TYPE_5__ {int field; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ISIF_BUFTYPE_FLD_INTERLEAVED ; 
 int /*<<< orphan*/  ISIF_BUFTYPE_FLD_SEPARATED ; 
 int ISIF_FRMFMT_INTERLACED ; 
 int ISIF_FRMFMT_PROGRESSIVE ; 
#define  V4L2_FIELD_INTERLACED 130 
#define  V4L2_FIELD_NONE 129 
#define  V4L2_FIELD_SEQ_TB 128 
 int isif_set_buftype (struct vpfe_isif_device*,int /*<<< orphan*/ ) ; 
 int isif_set_frame_format (struct vpfe_isif_device*,int) ; 
 int /*<<< orphan*/  isif_set_image_window (struct vpfe_isif_device*) ; 
 scalar_t__ isif_set_pixel_format (struct vpfe_isif_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbus_to_pix (TYPE_2__*,struct v4l2_pix_format*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (struct v4l2_pix_format*,TYPE_2__*) ; 

__attribute__((used)) static int
isif_config_format(struct vpfe_device *vpfe_dev, unsigned int pad)
{
	struct vpfe_isif_device *vpfe_isif = &vpfe_dev->vpfe_isif;
	enum isif_frmfmt frm_fmt = ISIF_FRMFMT_INTERLACED;
	struct v4l2_pix_format format;
	int ret = 0;

	v4l2_fill_pix_format(&format, &vpfe_dev->vpfe_isif.formats[pad]);
	mbus_to_pix(&vpfe_dev->vpfe_isif.formats[pad], &format);

	if (isif_set_pixel_format(vpfe_isif, format.pixelformat) < 0) {
		v4l2_err(&vpfe_dev->v4l2_dev,
			 "Failed to set pixel format in isif\n");
		return -EINVAL;
	}

	/* call for s_crop will override these values */
	vpfe_isif->crop.left = 0;
	vpfe_isif->crop.top = 0;
	vpfe_isif->crop.width = format.width;
	vpfe_isif->crop.height = format.height;

	/* configure the image window */
	isif_set_image_window(vpfe_isif);

	switch (vpfe_dev->vpfe_isif.formats[pad].field) {
	case V4L2_FIELD_INTERLACED:
		/* do nothing, since it is default */
		ret = isif_set_buftype(vpfe_isif, ISIF_BUFTYPE_FLD_INTERLEAVED);
		break;

	case V4L2_FIELD_NONE:
		frm_fmt = ISIF_FRMFMT_PROGRESSIVE;
		/* buffer type only applicable for interlaced scan */
		break;

	case V4L2_FIELD_SEQ_TB:
		ret = isif_set_buftype(vpfe_isif, ISIF_BUFTYPE_FLD_SEPARATED);
		break;

	default:
		return -EINVAL;
	}

	/* set the frame format */
	if (!ret)
		ret = isif_set_frame_format(vpfe_isif, frm_fmt);

	return ret;
}