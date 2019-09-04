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
typedef  int u32 ;
struct TYPE_4__ {int width; } ;
struct isif_ycbcr_config {int frm_fmt; int fid_pol; int hd_pol; int vd_pol; int pix_order; scalar_t__ buf_type; TYPE_2__ win; } ;
struct TYPE_3__ {int /*<<< orphan*/  base_addr; struct isif_ycbcr_config ycbcr; } ;
struct vpfe_isif_device {TYPE_1__ isif_cfg; struct v4l2_mbus_framefmt* formats; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int code; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDCFG ; 
 int DM365_ISIF_HSIZE_MASK ; 
 int DM365_ISIF_SDOFST_2_LINES ; 
 int EINVAL ; 
 int /*<<< orphan*/  HSIZE ; 
 scalar_t__ ISIF_BUFTYPE_FLD_INTERLEAVED ; 
 int ISIF_BW656_ENABLE ; 
 int ISIF_FID_POL_MASK ; 
 int ISIF_FID_POL_SHIFT ; 
 int ISIF_FRMFMT_INTERLACED ; 
 int ISIF_FRM_FMT_MASK ; 
 int ISIF_FRM_FMT_SHIFT ; 
 int ISIF_HD_POL_MASK ; 
 int ISIF_HD_POL_SHIFT ; 
 int ISIF_INPUT_MASK ; 
 int ISIF_INPUT_SHIFT ; 
 int ISIF_PACK_8BIT ; 
 size_t ISIF_PAD_SINK ; 
 int ISIF_PIXFMT_YCBCR_16BIT ; 
 int ISIF_PIXFMT_YCBCR_8BIT ; 
 int ISIF_PIX_ORDER_MASK ; 
 int ISIF_PIX_ORDER_SHIFT ; 
 int ISIF_VD_POL_MASK ; 
 int ISIF_VD_POL_SHIFT ; 
 int ISIF_YCINSWP_YCBCR ; 
#define  MEDIA_BUS_FMT_UYVY8_2X8 133 
#define  MEDIA_BUS_FMT_Y8_1X8 132 
#define  MEDIA_BUS_FMT_YUYV10_1X20 131 
#define  MEDIA_BUS_FMT_YUYV10_2X10 130 
#define  MEDIA_BUS_FMT_YUYV8_1X16 129 
#define  MEDIA_BUS_FMT_YUYV8_2X8 128 
 int /*<<< orphan*/  MODESET ; 
 int /*<<< orphan*/  REC656IF ; 
 int /*<<< orphan*/  SDOFST ; 
 int VPFE_PINPOL_NEGATIVE ; 
 int isif_get_pix_fmt (int) ; 
 int /*<<< orphan*/  isif_setwin (struct vpfe_isif_device*,TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  isif_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct vpfe_isif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int isif_config_ycbcr(struct v4l2_subdev *sd, int mode)
{
	struct vpfe_isif_device *isif = v4l2_get_subdevdata(sd);
	struct isif_ycbcr_config *params = &isif->isif_cfg.ycbcr;
	struct v4l2_mbus_framefmt *format;
	int pix_fmt;
	u32 modeset;
	u32 ccdcfg;

	format = &isif->formats[ISIF_PAD_SINK];
	/*
	 * first reset the ISIF
	 * all registers have default values after reset
	 * This is important since we assume default values to be set in
	 * a lot of registers that we didn't touch
	 */
	/* start with all bits zero */
	ccdcfg = 0;
	modeset = 0;
	pix_fmt = isif_get_pix_fmt(format->code);
	if (pix_fmt < 0) {
		pr_debug("Invalid pix_fmt(input mode)\n");
		return -EINVAL;
	}
	/* configure pixel format or input mode */
	modeset = modeset | ((pix_fmt & ISIF_INPUT_MASK) <<
		  ISIF_INPUT_SHIFT) | ((params->frm_fmt & ISIF_FRM_FMT_MASK) <<
		  ISIF_FRM_FMT_SHIFT) | (((params->fid_pol &
		  ISIF_FID_POL_MASK) << ISIF_FID_POL_SHIFT)) |
		  (((params->hd_pol & ISIF_HD_POL_MASK) << ISIF_HD_POL_SHIFT)) |
		  (((params->vd_pol & ISIF_VD_POL_MASK) << ISIF_VD_POL_SHIFT));
	/* pack the data to 8-bit CCDCCFG */
	switch (format->code) {
	case MEDIA_BUS_FMT_YUYV8_2X8:
	case MEDIA_BUS_FMT_UYVY8_2X8:
		if (pix_fmt != ISIF_PIXFMT_YCBCR_8BIT) {
			pr_debug("Invalid pix_fmt(input mode)\n");
			return -EINVAL;
		}
		modeset |= ((VPFE_PINPOL_NEGATIVE & ISIF_VD_POL_MASK) <<
				ISIF_VD_POL_SHIFT);
		isif_write(isif->isif_cfg.base_addr, 3, REC656IF);
		ccdcfg = ccdcfg | ISIF_PACK_8BIT | ISIF_YCINSWP_YCBCR;
		break;

	case MEDIA_BUS_FMT_YUYV10_2X10:
		if (pix_fmt != ISIF_PIXFMT_YCBCR_8BIT) {
			pr_debug("Invalid pix_fmt(input mode)\n");
			return -EINVAL;
		}
		/* setup BT.656, embedded sync  */
		isif_write(isif->isif_cfg.base_addr, 3, REC656IF);
		/* enable 10 bit mode in ccdcfg */
		ccdcfg = ccdcfg | ISIF_PACK_8BIT | ISIF_YCINSWP_YCBCR |
			ISIF_BW656_ENABLE;
		break;

	case MEDIA_BUS_FMT_YUYV10_1X20:
		if (pix_fmt != ISIF_PIXFMT_YCBCR_16BIT) {
			pr_debug("Invalid pix_fmt(input mode)\n");
			return -EINVAL;
		}
		isif_write(isif->isif_cfg.base_addr, 3, REC656IF);
		break;

	case MEDIA_BUS_FMT_Y8_1X8:
		ccdcfg |= ISIF_PACK_8BIT;
		ccdcfg |= ISIF_YCINSWP_YCBCR;
		if (pix_fmt != ISIF_PIXFMT_YCBCR_8BIT) {
			pr_debug("Invalid pix_fmt(input mode)\n");
			return -EINVAL;
		}
		break;

	case MEDIA_BUS_FMT_YUYV8_1X16:
		if (pix_fmt != ISIF_PIXFMT_YCBCR_16BIT) {
			pr_debug("Invalid pix_fmt(input mode)\n");
			return -EINVAL;
		}
		break;

	default:
		/* should never come here */
		pr_debug("Invalid interface type\n");
		return -EINVAL;
	}
	isif_write(isif->isif_cfg.base_addr, modeset, MODESET);
	/* Set up pix order */
	ccdcfg |= (params->pix_order & ISIF_PIX_ORDER_MASK) <<
		ISIF_PIX_ORDER_SHIFT;
	isif_write(isif->isif_cfg.base_addr, ccdcfg, CCDCFG);
	/* configure video window */
	if (format->code == MEDIA_BUS_FMT_YUYV10_1X20 ||
			format->code == MEDIA_BUS_FMT_YUYV8_1X16)
		isif_setwin(isif, &params->win, params->frm_fmt, 1, mode);
	else
		isif_setwin(isif, &params->win, params->frm_fmt, 2, mode);

	/*
	 * configure the horizontal line offset
	 * this is done by rounding up width to a multiple of 16 pixels
	 * and multiply by two to account for y:cb:cr 4:2:2 data
	 */
	isif_write(isif->isif_cfg.base_addr,
		   ((((params->win.width * 2) + 31) &
		   DM365_ISIF_HSIZE_MASK) >> 5), HSIZE);

	/* configure the memory line offset */
	if (params->frm_fmt == ISIF_FRMFMT_INTERLACED &&
	    params->buf_type == ISIF_BUFTYPE_FLD_INTERLEAVED)
		/* two fields are interleaved in memory */
		isif_write(isif->isif_cfg.base_addr,
			   DM365_ISIF_SDOFST_2_LINES, SDOFST);
	return 0;
}