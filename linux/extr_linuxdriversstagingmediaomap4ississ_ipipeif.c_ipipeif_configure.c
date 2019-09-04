#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct v4l2_mbus_framefmt {int code; int width; int height; } ;
struct TYPE_2__ {int bpl_value; } ;
struct iss_ipipeif_device {TYPE_1__ video_out; struct v4l2_mbus_framefmt* formats; int /*<<< orphan*/  input; } ;
struct iss_format_info {int /*<<< orphan*/  bpp; } ;
struct iss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPIPEIF_CFG1 ; 
 int IPIPEIF_CFG1_INPSRC1_MASK ; 
 int IPIPEIF_CFG1_INPSRC2_MASK ; 
 int /*<<< orphan*/  IPIPEIF_CFG2 ; 
 int IPIPEIF_CFG2_YUV16 ; 
 int IPIPEIF_CFG2_YUV8 ; 
 size_t IPIPEIF_PAD_SINK ; 
 size_t IPIPEIF_PAD_SOURCE_ISIF_SF ; 
 int /*<<< orphan*/  ISIF_CCOLP ; 
 int ISIF_CCOLP_CP0_F0_B ; 
 int ISIF_CCOLP_CP0_F0_GB ; 
 int ISIF_CCOLP_CP0_F0_GR ; 
 int ISIF_CCOLP_CP0_F0_R ; 
 int ISIF_CCOLP_CP1_F0_B ; 
 int ISIF_CCOLP_CP1_F0_GB ; 
 int ISIF_CCOLP_CP1_F0_GR ; 
 int ISIF_CCOLP_CP1_F0_R ; 
 int ISIF_CCOLP_CP2_F0_B ; 
 int ISIF_CCOLP_CP2_F0_GB ; 
 int ISIF_CCOLP_CP2_F0_GR ; 
 int ISIF_CCOLP_CP2_F0_R ; 
 int ISIF_CCOLP_CP3_F0_B ; 
 int ISIF_CCOLP_CP3_F0_GB ; 
 int ISIF_CCOLP_CP3_F0_GR ; 
 int ISIF_CCOLP_CP3_F0_R ; 
 int /*<<< orphan*/  ISIF_CGAMMAWD ; 
 int ISIF_CGAMMAWD_GWDI (int /*<<< orphan*/ ) ; 
 int ISIF_CGAMMAWD_GWDI_MASK ; 
 int /*<<< orphan*/  ISIF_HSIZE ; 
 int ISIF_HSIZE_HSIZE_MASK ; 
 int /*<<< orphan*/  ISIF_LNH ; 
 int ISIF_LNH_MASK ; 
 int /*<<< orphan*/  ISIF_LNV ; 
 int ISIF_LNV_MASK ; 
 int /*<<< orphan*/  ISIF_MODESET ; 
 int ISIF_MODESET_CCDMD ; 
 int ISIF_MODESET_CCDW_2BIT ; 
 int ISIF_MODESET_CCDW_MASK ; 
 int ISIF_MODESET_INPMOD_MASK ; 
 int ISIF_MODESET_INPMOD_RAW ; 
 int ISIF_MODESET_INPMOD_YCBCR16 ; 
 int /*<<< orphan*/  ISIF_SPH ; 
 int ISIF_SPH_MASK ; 
 int /*<<< orphan*/  ISIF_VDINT (int /*<<< orphan*/ ) ; 
#define  MEDIA_BUS_FMT_SBGGR10_1X10 133 
#define  MEDIA_BUS_FMT_SGBRG10_1X10 132 
#define  MEDIA_BUS_FMT_SGRBG10_1X10 131 
#define  MEDIA_BUS_FMT_SRGGB10_1X10 130 
#define  MEDIA_BUS_FMT_UYVY8_1X16 129 
#define  MEDIA_BUS_FMT_YUYV8_1X16 128 
 int /*<<< orphan*/  OMAP4_ISS_MEM_ISP_IPIPEIF ; 
 int /*<<< orphan*/  OMAP4_ISS_MEM_ISP_ISIF ; 
 int /*<<< orphan*/  iss_reg_clr (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iss_reg_update (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  iss_reg_write (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap4iss_configure_bridge (struct iss_device*,int /*<<< orphan*/ ) ; 
 struct iss_format_info* omap4iss_video_format_info (int) ; 
 struct iss_device* to_iss_device (struct iss_ipipeif_device*) ; 

__attribute__((used)) static void ipipeif_configure(struct iss_ipipeif_device *ipipeif)
{
	struct iss_device *iss = to_iss_device(ipipeif);
	const struct iss_format_info *info;
	struct v4l2_mbus_framefmt *format;
	u32 isif_ccolp = 0;

	omap4iss_configure_bridge(iss, ipipeif->input);

	/* IPIPEIF_PAD_SINK */
	format = &ipipeif->formats[IPIPEIF_PAD_SINK];

	/* IPIPEIF with YUV422 input from ISIF */
	iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_IPIPEIF, IPIPEIF_CFG1,
		    IPIPEIF_CFG1_INPSRC1_MASK | IPIPEIF_CFG1_INPSRC2_MASK);

	/* Select ISIF/IPIPEIF input format */
	switch (format->code) {
	case MEDIA_BUS_FMT_UYVY8_1X16:
	case MEDIA_BUS_FMT_YUYV8_1X16:
		iss_reg_update(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_MODESET,
			       ISIF_MODESET_CCDMD | ISIF_MODESET_INPMOD_MASK |
			       ISIF_MODESET_CCDW_MASK,
			       ISIF_MODESET_INPMOD_YCBCR16);

		iss_reg_update(iss, OMAP4_ISS_MEM_ISP_IPIPEIF, IPIPEIF_CFG2,
			       IPIPEIF_CFG2_YUV8, IPIPEIF_CFG2_YUV16);

		break;
	case MEDIA_BUS_FMT_SGRBG10_1X10:
		isif_ccolp = ISIF_CCOLP_CP0_F0_GR |
			ISIF_CCOLP_CP1_F0_R |
			ISIF_CCOLP_CP2_F0_B |
			ISIF_CCOLP_CP3_F0_GB;
		goto cont_raw;
	case MEDIA_BUS_FMT_SRGGB10_1X10:
		isif_ccolp = ISIF_CCOLP_CP0_F0_R |
			ISIF_CCOLP_CP1_F0_GR |
			ISIF_CCOLP_CP2_F0_GB |
			ISIF_CCOLP_CP3_F0_B;
		goto cont_raw;
	case MEDIA_BUS_FMT_SBGGR10_1X10:
		isif_ccolp = ISIF_CCOLP_CP0_F0_B |
			ISIF_CCOLP_CP1_F0_GB |
			ISIF_CCOLP_CP2_F0_GR |
			ISIF_CCOLP_CP3_F0_R;
		goto cont_raw;
	case MEDIA_BUS_FMT_SGBRG10_1X10:
		isif_ccolp = ISIF_CCOLP_CP0_F0_GB |
			ISIF_CCOLP_CP1_F0_B |
			ISIF_CCOLP_CP2_F0_R |
			ISIF_CCOLP_CP3_F0_GR;
cont_raw:
		iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_IPIPEIF, IPIPEIF_CFG2,
			    IPIPEIF_CFG2_YUV16);

		iss_reg_update(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_MODESET,
			       ISIF_MODESET_CCDMD | ISIF_MODESET_INPMOD_MASK |
			       ISIF_MODESET_CCDW_MASK, ISIF_MODESET_INPMOD_RAW |
			       ISIF_MODESET_CCDW_2BIT);

		info = omap4iss_video_format_info(format->code);
		iss_reg_update(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_CGAMMAWD,
			       ISIF_CGAMMAWD_GWDI_MASK,
			       ISIF_CGAMMAWD_GWDI(info->bpp));

		/* Set RAW Bayer pattern */
		iss_reg_write(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_CCOLP,
			      isif_ccolp);
		break;
	}

	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_SPH, 0 & ISIF_SPH_MASK);
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_LNH,
		      (format->width - 1) & ISIF_LNH_MASK);
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_LNV,
		      (format->height - 1) & ISIF_LNV_MASK);

	/* Generate ISIF0 on the last line of the image */
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_VDINT(0),
		      format->height - 1);

	/* IPIPEIF_PAD_SOURCE_ISIF_SF */
	format = &ipipeif->formats[IPIPEIF_PAD_SOURCE_ISIF_SF];

	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_HSIZE,
		      (ipipeif->video_out.bpl_value >> 5) &
		      ISIF_HSIZE_HSIZE_MASK);

	/* IPIPEIF_PAD_SOURCE_VP */
	/* Do nothing? */
}