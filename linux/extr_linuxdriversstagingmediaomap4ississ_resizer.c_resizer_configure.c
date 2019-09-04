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
struct v4l2_mbus_framefmt {int height; int width; scalar_t__ code; } ;
struct TYPE_2__ {int bpl_value; } ;
struct iss_resizer_device {scalar_t__ input; TYPE_1__ video_out; struct v4l2_mbus_framefmt* formats; } ;
struct iss_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ MEDIA_BUS_FMT_UYVY8_1X16 ; 
 scalar_t__ MEDIA_BUS_FMT_YUYV8_1_5X8 ; 
 int /*<<< orphan*/  OMAP4_ISS_MEM_ISP_RESIZER ; 
 scalar_t__ RESIZER_INPUT_IPIPEIF ; 
 size_t RESIZER_PAD_SINK ; 
 size_t RESIZER_PAD_SOURCE_MEM ; 
 int RSZ_420_CEN ; 
 int RSZ_420_YEN ; 
 int /*<<< orphan*/  RSZ_SRC_FMT0 ; 
 int /*<<< orphan*/  RSZ_SRC_FMT0_BYPASS ; 
 int /*<<< orphan*/  RSZ_SRC_FMT0_SEL ; 
 int /*<<< orphan*/  RSZ_SRC_HPS ; 
 int /*<<< orphan*/  RSZ_SRC_HSZ ; 
 int /*<<< orphan*/  RSZ_SRC_MODE ; 
 int /*<<< orphan*/  RSZ_SRC_MODE_OST ; 
 int /*<<< orphan*/  RSZ_SRC_MODE_WRT ; 
 int /*<<< orphan*/  RSZ_SRC_VPS ; 
 int /*<<< orphan*/  RSZ_SRC_VSZ ; 
 int /*<<< orphan*/  RZA_420 ; 
 int /*<<< orphan*/  RZA_H_DIF ; 
 int /*<<< orphan*/  RZA_I_HPS ; 
 int /*<<< orphan*/  RZA_I_VPS ; 
 int /*<<< orphan*/  RZA_MODE ; 
 int /*<<< orphan*/  RZA_MODE_ONE_SHOT ; 
 int /*<<< orphan*/  RZA_O_HSZ ; 
 int /*<<< orphan*/  RZA_O_VSZ ; 
 int /*<<< orphan*/  RZA_SDR_C_OFT ; 
 int /*<<< orphan*/  RZA_SDR_C_PTR_E ; 
 int /*<<< orphan*/  RZA_SDR_C_PTR_S ; 
 int /*<<< orphan*/  RZA_SDR_Y_OFT ; 
 int /*<<< orphan*/  RZA_SDR_Y_PTR_E ; 
 int /*<<< orphan*/  RZA_SDR_Y_PTR_S ; 
 int /*<<< orphan*/  RZA_V_DIF ; 
 int /*<<< orphan*/  iss_reg_clr (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_update (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_write (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct iss_device* to_iss_device (struct iss_resizer_device*) ; 

__attribute__((used)) static void resizer_configure(struct iss_resizer_device *resizer)
{
	struct iss_device *iss = to_iss_device(resizer);
	struct v4l2_mbus_framefmt *informat, *outformat;

	informat = &resizer->formats[RESIZER_PAD_SINK];
	outformat = &resizer->formats[RESIZER_PAD_SOURCE_MEM];

	/* Disable pass-through more. Despite its name, the BYPASS bit controls
	 * pass-through mode, not bypass mode.
	 */
	iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_FMT0,
		    RSZ_SRC_FMT0_BYPASS);

	/* Select RSZ input */
	iss_reg_update(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_FMT0,
		       RSZ_SRC_FMT0_SEL,
		       resizer->input == RESIZER_INPUT_IPIPEIF ?
		       RSZ_SRC_FMT0_SEL : 0);

	/* RSZ ignores WEN signal from IPIPE/IPIPEIF */
	iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_MODE,
		    RSZ_SRC_MODE_WRT);

	/* Set Resizer in free-running mode */
	iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_MODE,
		    RSZ_SRC_MODE_OST);

	/* Init Resizer A */
	iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_MODE,
		    RZA_MODE_ONE_SHOT);

	/* Set size related things now */
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_VPS, 0);
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_HPS, 0);
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_VSZ,
		      informat->height - 2);
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SRC_HSZ,
		      informat->width - 1);

	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_I_VPS, 0);
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_I_HPS, 0);

	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_O_VSZ,
		      outformat->height - 2);
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_O_HSZ,
		      outformat->width - 1);

	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_V_DIF, 0x100);
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_H_DIF, 0x100);

	/* Buffer output settings */
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_Y_PTR_S, 0);
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_Y_PTR_E,
		      outformat->height - 1);

	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_Y_OFT,
		      resizer->video_out.bpl_value);

	/* UYVY -> NV12 conversion */
	if ((informat->code == MEDIA_BUS_FMT_UYVY8_1X16) &&
	    (outformat->code == MEDIA_BUS_FMT_YUYV8_1_5X8)) {
		iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_420,
			      RSZ_420_CEN | RSZ_420_YEN);

		/* UV Buffer output settings */
		iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_C_PTR_S,
			      0);
		iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_C_PTR_E,
			      outformat->height - 1);

		iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_C_OFT,
			      resizer->video_out.bpl_value);
	} else {
		iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_420, 0);
	}
}