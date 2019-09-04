#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  df_or_csc; } ;
struct vpfe_isif_raw_config {int horz_offset; int vert_offset; int /*<<< orphan*/  culling; int /*<<< orphan*/  linearize; TYPE_3__ df_csc; int /*<<< orphan*/  dfc; int /*<<< orphan*/  bclamp; } ;
struct TYPE_5__ {int width; } ;
struct isif_params_raw {int vd_pol; int hd_pol; int fid_pol; int frm_fmt; int cfa_pat; scalar_t__ v4l2_pix_fmt; int data_msb; int dpcm_predictor; int horz_flip_en; TYPE_2__ win; scalar_t__ image_invert_en; struct vpfe_isif_raw_config config_params; } ;
struct TYPE_4__ {int data_pack; int /*<<< orphan*/  base_addr; struct isif_params_raw bayer; } ;
struct vpfe_isif_device {TYPE_1__ isif_cfg; struct v4l2_mbus_framefmt* formats; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDCFG ; 
 int /*<<< orphan*/  CCOLP ; 
 int /*<<< orphan*/  CGAMMAWD ; 
 int /*<<< orphan*/  DATAHOFST ; 
 int /*<<< orphan*/  DATAVOFST ; 
 int EINVAL ; 
 int /*<<< orphan*/  HSIZE ; 
 int ISIF_ALAW_ENABLE ; 
 int ISIF_ALAW_GAMA_WD_MASK ; 
 int ISIF_ALAW_GAMA_WD_SHIFT ; 
 int ISIF_CCDCFG_EXTRG_DISABLE ; 
 int ISIF_CCDCFG_FIDMD_LATCH_VSYNC ; 
 int ISIF_CCDCFG_TRGSEL_WEN ; 
 int ISIF_CCDCFG_WENLOG_AND ; 
 int ISIF_DATAPOL_MASK ; 
 int ISIF_DATAPOL_NORMAL ; 
 int ISIF_DATAPOL_SHIFT ; 
 int ISIF_DATASFT_MASK ; 
 int ISIF_DATASFT_SHIFT ; 
 int ISIF_DATA_H_OFFSET_MASK ; 
 int ISIF_DATA_PACK_MASK ; 
 int ISIF_DATA_V_OFFSET_MASK ; 
 int ISIF_DPCM_EN_SHIFT ; 
 int ISIF_DPCM_PREDICTOR_MASK ; 
 int ISIF_DPCM_PREDICTOR_SHIFT ; 
 int ISIF_EXWEN_DISABLE ; 
 int ISIF_EXWEN_MASK ; 
 int ISIF_EXWEN_SHIFT ; 
 int ISIF_FID_POL_MASK ; 
 int ISIF_FID_POL_SHIFT ; 
 int ISIF_FRMFMT_INTERLACED ; 
 int ISIF_FRMFMT_PROGRESSIVE ; 
 int ISIF_FRM_FMT_MASK ; 
 int ISIF_FRM_FMT_SHIFT ; 
 int ISIF_GAMMAWD_CFA_MASK ; 
 int ISIF_GAMMAWD_CFA_SHIFT ; 
 int ISIF_HD_POL_MASK ; 
 int ISIF_HD_POL_SHIFT ; 
 int ISIF_HSIZE_FLIP_MASK ; 
 int ISIF_HSIZE_FLIP_SHIFT ; 
 int ISIF_INPUT_MASK ; 
 int ISIF_INPUT_SHIFT ; 
 int ISIF_INTERLACE_INVERSE_MODE ; 
 int ISIF_INTERLACE_NON_INVERSE_MODE ; 
 int ISIF_LINEOFST_MASK ; 
 int ISIF_PACK_12BIT ; 
 int ISIF_PACK_8BIT ; 
 size_t ISIF_PAD_SINK ; 
 int ISIF_PROGRESSIVE_INVERSE_MODE ; 
 int ISIF_PROGRESSIVE_NON_INVERSE_MODE ; 
 int ISIF_VDHDOUT_INPUT ; 
 int ISIF_VD_POL_MASK ; 
 int ISIF_VD_POL_SHIFT ; 
 int ISIF_YCINSWP_RAW ; 
 scalar_t__ MEDIA_BUS_FMT_SGRBG12_1X12 ; 
 int /*<<< orphan*/  MISC ; 
 int /*<<< orphan*/  MODESET ; 
 int /*<<< orphan*/  REC656IF ; 
 int /*<<< orphan*/  SDOFST ; 
 scalar_t__ V4L2_PIX_FMT_SGRBG10ALAW8 ; 
 scalar_t__ V4L2_PIX_FMT_SGRBG10DPCM8 ; 
 int VPFE_ISIF_NO_SHIFT ; 
 int /*<<< orphan*/  isif_config_bclamp (struct vpfe_isif_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isif_config_csc (struct vpfe_isif_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  isif_config_culling (struct vpfe_isif_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isif_config_dfc (struct vpfe_isif_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isif_config_gain_offset (struct vpfe_isif_device*) ; 
 int /*<<< orphan*/  isif_config_linearization (struct vpfe_isif_device*,int /*<<< orphan*/ *) ; 
 int isif_get_pix_fmt (scalar_t__) ; 
 int /*<<< orphan*/  isif_setwin (struct vpfe_isif_device*,TYPE_2__*,int,int,int) ; 
 int isif_sgrbg_pattern ; 
 int isif_srggb_pattern ; 
 int /*<<< orphan*/  isif_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct vpfe_isif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int isif_config_raw(struct v4l2_subdev *sd, int mode)
{
	struct vpfe_isif_device *isif = v4l2_get_subdevdata(sd);
	struct isif_params_raw *params = &isif->isif_cfg.bayer;
	struct vpfe_isif_raw_config *module_params =
				&isif->isif_cfg.bayer.config_params;
	struct v4l2_mbus_framefmt *format;
	int pix_fmt;
	u32 val;

	format = &isif->formats[ISIF_PAD_SINK];

	/* In case of user has set BT656IF earlier, it should be reset
	 * when configuring for raw input.
	 */
	isif_write(isif->isif_cfg.base_addr, 0, REC656IF);
	/* Configure CCDCFG register
	 * Set CCD Not to swap input since input is RAW data
	 * Set FID detection function to Latch at V-Sync
	 * Set WENLOG - isif valid area
	 * Set TRGSEL
	 * Set EXTRG
	 * Packed to 8 or 16 bits
	 */
	val = ISIF_YCINSWP_RAW | ISIF_CCDCFG_FIDMD_LATCH_VSYNC |
	      ISIF_CCDCFG_WENLOG_AND | ISIF_CCDCFG_TRGSEL_WEN |
	      ISIF_CCDCFG_EXTRG_DISABLE | (isif->isif_cfg.data_pack &
	      ISIF_DATA_PACK_MASK);
	isif_write(isif->isif_cfg.base_addr, val, CCDCFG);

	pix_fmt = isif_get_pix_fmt(format->code);
	if (pix_fmt < 0) {
		pr_debug("Invalid pix_fmt(input mode)\n");
		return -EINVAL;
	}
	/*
	 * Configure the vertical sync polarity(MODESET.VDPOL)
	 * Configure the horizontal sync polarity (MODESET.HDPOL)
	 * Configure frame id polarity (MODESET.FLDPOL)
	 * Configure data polarity
	 * Configure External WEN Selection
	 * Configure frame format(progressive or interlace)
	 * Configure pixel format (Input mode)
	 * Configure the data shift
	 */
	val = ISIF_VDHDOUT_INPUT | ((params->vd_pol & ISIF_VD_POL_MASK) <<
	      ISIF_VD_POL_SHIFT) | ((params->hd_pol & ISIF_HD_POL_MASK) <<
	      ISIF_HD_POL_SHIFT) | ((params->fid_pol & ISIF_FID_POL_MASK) <<
	      ISIF_FID_POL_SHIFT) | ((ISIF_DATAPOL_NORMAL &
	      ISIF_DATAPOL_MASK) << ISIF_DATAPOL_SHIFT) | ((ISIF_EXWEN_DISABLE &
	      ISIF_EXWEN_MASK) << ISIF_EXWEN_SHIFT) | ((params->frm_fmt &
	      ISIF_FRM_FMT_MASK) << ISIF_FRM_FMT_SHIFT) | ((pix_fmt &
	      ISIF_INPUT_MASK) << ISIF_INPUT_SHIFT);

	/* currently only MEDIA_BUS_FMT_SGRBG12_1X12 is
	 * supported. shift appropriately depending on
	 * different MBUS fmt's added
	 */
	if (format->code == MEDIA_BUS_FMT_SGRBG12_1X12)
		val |= ((VPFE_ISIF_NO_SHIFT &
			ISIF_DATASFT_MASK) << ISIF_DATASFT_SHIFT);

	isif_write(isif->isif_cfg.base_addr, val, MODESET);
	/*
	 * Configure GAMMAWD register
	 * CFA pattern setting
	 */
	val = (params->cfa_pat & ISIF_GAMMAWD_CFA_MASK) <<
		ISIF_GAMMAWD_CFA_SHIFT;
	/* Gamma msb */
	if (params->v4l2_pix_fmt == V4L2_PIX_FMT_SGRBG10ALAW8)
		val = val | ISIF_ALAW_ENABLE;

	val = val | ((params->data_msb & ISIF_ALAW_GAMA_WD_MASK) <<
			ISIF_ALAW_GAMA_WD_SHIFT);

	isif_write(isif->isif_cfg.base_addr, val, CGAMMAWD);
	/* Configure DPCM compression settings */
	if (params->v4l2_pix_fmt == V4L2_PIX_FMT_SGRBG10DPCM8) {
		val =  1 << ISIF_DPCM_EN_SHIFT;
		val |= (params->dpcm_predictor &
			ISIF_DPCM_PREDICTOR_MASK) << ISIF_DPCM_PREDICTOR_SHIFT;
	}
	isif_write(isif->isif_cfg.base_addr, val, MISC);
	/* Configure Gain & Offset */
	isif_config_gain_offset(isif);
	/* Configure Color pattern */
	if (format->code == MEDIA_BUS_FMT_SGRBG12_1X12)
		val = isif_sgrbg_pattern;
	else
		/* default set to rggb */
		val = isif_srggb_pattern;

	isif_write(isif->isif_cfg.base_addr, val, CCOLP);

	/* Configure HSIZE register  */
	val = (params->horz_flip_en & ISIF_HSIZE_FLIP_MASK) <<
	      ISIF_HSIZE_FLIP_SHIFT;

	/* calculate line offset in 32 bytes based on pack value */
	if (isif->isif_cfg.data_pack == ISIF_PACK_8BIT)
		val |= ((params->win.width + 31) >> 5) & ISIF_LINEOFST_MASK;
	else if (isif->isif_cfg.data_pack == ISIF_PACK_12BIT)
		val |= ((((params->win.width + (params->win.width >> 2)) +
			31) >> 5) & ISIF_LINEOFST_MASK);
	else
		val |= (((params->win.width * 2) + 31) >> 5) &
			ISIF_LINEOFST_MASK;
	isif_write(isif->isif_cfg.base_addr, val, HSIZE);
	/* Configure SDOFST register  */
	if (params->frm_fmt == ISIF_FRMFMT_INTERLACED) {
		if (params->image_invert_en)
			/* For interlace inverse mode */
			isif_write(isif->isif_cfg.base_addr,
				   ISIF_INTERLACE_INVERSE_MODE, SDOFST);
		else
			/* For interlace non inverse mode */
			isif_write(isif->isif_cfg.base_addr,
				   ISIF_INTERLACE_NON_INVERSE_MODE, SDOFST);
	} else if (params->frm_fmt == ISIF_FRMFMT_PROGRESSIVE) {
		if (params->image_invert_en)
			isif_write(isif->isif_cfg.base_addr,
				   ISIF_PROGRESSIVE_INVERSE_MODE, SDOFST);
		else
			/* For progessive non inverse mode */
			isif_write(isif->isif_cfg.base_addr,
				   ISIF_PROGRESSIVE_NON_INVERSE_MODE, SDOFST);
	}
	/* Configure video window */
	isif_setwin(isif, &params->win, params->frm_fmt, 1, mode);
	/* Configure Black Clamp */
	isif_config_bclamp(isif, &module_params->bclamp);
	/* Configure Vertical Defection Pixel Correction */
	isif_config_dfc(isif, &module_params->dfc);
	if (!module_params->df_csc.df_or_csc)
		/* Configure Color Space Conversion */
		isif_config_csc(isif, &module_params->df_csc);

	isif_config_linearization(isif, &module_params->linearize);
	/* Configure Culling */
	isif_config_culling(isif, &module_params->culling);
	/* Configure Horizontal and vertical offsets(DFC,LSC,Gain) */
	val = module_params->horz_offset & ISIF_DATA_H_OFFSET_MASK;
	isif_write(isif->isif_cfg.base_addr, val, DATAHOFST);

	val = module_params->vert_offset & ISIF_DATA_V_OFFSET_MASK;
	isif_write(isif->isif_cfg.base_addr, val, DATAVOFST);

	return 0;
}