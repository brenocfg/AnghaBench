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
struct TYPE_5__ {int /*<<< orphan*/  data_msb; int /*<<< orphan*/  cfa_pat; void* hd_pol; void* vd_pol; void* fid_pol; int /*<<< orphan*/  frm_fmt; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  v4l2_pix_fmt; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf_type; int /*<<< orphan*/  pix_order; void* hd_pol; void* vd_pol; void* fid_pol; int /*<<< orphan*/  frm_fmt; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  v4l2_pix_fmt; } ;
struct TYPE_6__ {int /*<<< orphan*/  data_pack; TYPE_2__ bayer; TYPE_1__ ycbcr; } ;
struct vpfe_isif_device {TYPE_3__ isif_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISIF_BIT_MSB_11 ; 
 int /*<<< orphan*/  ISIF_BUFTYPE_FLD_INTERLEAVED ; 
 int /*<<< orphan*/  ISIF_CFA_PAT_MOSAIC ; 
 int /*<<< orphan*/  ISIF_FRMFMT_INTERLACED ; 
 int /*<<< orphan*/  ISIF_FRMFMT_PROGRESSIVE ; 
 int /*<<< orphan*/  ISIF_PACK_8BIT ; 
 int /*<<< orphan*/  ISIF_PIXFMT_RAW ; 
 int /*<<< orphan*/  ISIF_PIXFMT_YCBCR_8BIT ; 
 int /*<<< orphan*/  ISIF_PIXORDER_CBYCRY ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_SGRBG10ALAW8 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_UYVY ; 
 void* VPFE_PINPOL_POSITIVE ; 

__attribute__((used)) static void isif_config_defaults(struct vpfe_isif_device *isif)
{
	isif->isif_cfg.ycbcr.v4l2_pix_fmt = V4L2_PIX_FMT_UYVY;
	isif->isif_cfg.ycbcr.pix_fmt = ISIF_PIXFMT_YCBCR_8BIT;
	isif->isif_cfg.ycbcr.frm_fmt = ISIF_FRMFMT_INTERLACED;
	isif->isif_cfg.ycbcr.fid_pol = VPFE_PINPOL_POSITIVE;
	isif->isif_cfg.ycbcr.vd_pol = VPFE_PINPOL_POSITIVE;
	isif->isif_cfg.ycbcr.hd_pol = VPFE_PINPOL_POSITIVE;
	isif->isif_cfg.ycbcr.pix_order = ISIF_PIXORDER_CBYCRY;
	isif->isif_cfg.ycbcr.buf_type = ISIF_BUFTYPE_FLD_INTERLEAVED;

	isif->isif_cfg.bayer.v4l2_pix_fmt = V4L2_PIX_FMT_SGRBG10ALAW8;
	isif->isif_cfg.bayer.pix_fmt = ISIF_PIXFMT_RAW;
	isif->isif_cfg.bayer.frm_fmt = ISIF_FRMFMT_PROGRESSIVE;
	isif->isif_cfg.bayer.fid_pol = VPFE_PINPOL_POSITIVE;
	isif->isif_cfg.bayer.vd_pol = VPFE_PINPOL_POSITIVE;
	isif->isif_cfg.bayer.hd_pol = VPFE_PINPOL_POSITIVE;
	isif->isif_cfg.bayer.cfa_pat = ISIF_CFA_PAT_MOSAIC;
	isif->isif_cfg.bayer.data_msb = ISIF_BIT_MSB_11;
	isif->isif_cfg.data_pack = ISIF_PACK_8BIT;
}