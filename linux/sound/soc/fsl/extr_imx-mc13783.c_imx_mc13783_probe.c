#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int IMX_AUDMUX_V1_PCR_RCLKDIR ; 
 int IMX_AUDMUX_V1_PCR_RFCSEL (int /*<<< orphan*/ ) ; 
 int IMX_AUDMUX_V1_PCR_RFSDIR ; 
 int IMX_AUDMUX_V1_PCR_RXDSEL (int /*<<< orphan*/ ) ; 
 int IMX_AUDMUX_V1_PCR_SYN ; 
 int IMX_AUDMUX_V1_PCR_TCLKDIR ; 
 int IMX_AUDMUX_V1_PCR_TFCSEL (int /*<<< orphan*/ ) ; 
 int IMX_AUDMUX_V1_PCR_TFSDIR ; 
 int IMX_AUDMUX_V2_PDCR_INMMASK (int) ; 
 int IMX_AUDMUX_V2_PDCR_MODE (int) ; 
 int IMX_AUDMUX_V2_PDCR_RXDSEL (int /*<<< orphan*/ ) ; 
 int IMX_AUDMUX_V2_PTCR_RCLKDIR ; 
 int IMX_AUDMUX_V2_PTCR_RCSEL (int /*<<< orphan*/ ) ; 
 int IMX_AUDMUX_V2_PTCR_RFSDIR ; 
 int IMX_AUDMUX_V2_PTCR_RFSEL (int /*<<< orphan*/ ) ; 
 int IMX_AUDMUX_V2_PTCR_SYN ; 
 int IMX_AUDMUX_V2_PTCR_TCLKDIR ; 
 int IMX_AUDMUX_V2_PTCR_TCSEL (int /*<<< orphan*/ ) ; 
 int IMX_AUDMUX_V2_PTCR_TFSDIR ; 
 int IMX_AUDMUX_V2_PTCR_TFSEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MX27_AUDMUX_HPCR1_SSI0 ; 
 int /*<<< orphan*/  MX27_AUDMUX_HPCR3_SSI_PINS_4 ; 
 int /*<<< orphan*/  MX31_AUDMUX_PORT1_SSI0 ; 
 int /*<<< orphan*/  MX31_AUDMUX_PORT4_SSI_PINS_4 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  imx_audmux_v1_configure_port (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imx_audmux_v2_configure_port (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__ imx_mc13783 ; 
 scalar_t__ machine_is_mx27_3ds () ; 
 scalar_t__ machine_is_mx31_3ds () ; 
 scalar_t__ machine_is_mx31moboard () ; 
 int snd_soc_register_card (TYPE_1__*) ; 

__attribute__((used)) static int imx_mc13783_probe(struct platform_device *pdev)
{
	int ret;

	imx_mc13783.dev = &pdev->dev;

	ret = snd_soc_register_card(&imx_mc13783);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n",
			ret);
		return ret;
	}

	if (machine_is_mx31_3ds() || machine_is_mx31moboard()) {
		imx_audmux_v2_configure_port(MX31_AUDMUX_PORT4_SSI_PINS_4,
			IMX_AUDMUX_V2_PTCR_SYN,
			IMX_AUDMUX_V2_PDCR_RXDSEL(MX31_AUDMUX_PORT1_SSI0) |
			IMX_AUDMUX_V2_PDCR_MODE(1) |
			IMX_AUDMUX_V2_PDCR_INMMASK(0xfc));
		imx_audmux_v2_configure_port(MX31_AUDMUX_PORT1_SSI0,
			IMX_AUDMUX_V2_PTCR_SYN |
			IMX_AUDMUX_V2_PTCR_TFSDIR |
			IMX_AUDMUX_V2_PTCR_TFSEL(MX31_AUDMUX_PORT4_SSI_PINS_4) |
			IMX_AUDMUX_V2_PTCR_TCLKDIR |
			IMX_AUDMUX_V2_PTCR_TCSEL(MX31_AUDMUX_PORT4_SSI_PINS_4) |
			IMX_AUDMUX_V2_PTCR_RFSDIR |
			IMX_AUDMUX_V2_PTCR_RFSEL(MX31_AUDMUX_PORT4_SSI_PINS_4) |
			IMX_AUDMUX_V2_PTCR_RCLKDIR |
			IMX_AUDMUX_V2_PTCR_RCSEL(MX31_AUDMUX_PORT4_SSI_PINS_4),
			IMX_AUDMUX_V2_PDCR_RXDSEL(MX31_AUDMUX_PORT4_SSI_PINS_4));
	} else if (machine_is_mx27_3ds()) {
		imx_audmux_v1_configure_port(MX27_AUDMUX_HPCR1_SSI0,
			IMX_AUDMUX_V1_PCR_SYN |
			IMX_AUDMUX_V1_PCR_TFSDIR |
			IMX_AUDMUX_V1_PCR_TCLKDIR |
			IMX_AUDMUX_V1_PCR_RFSDIR |
			IMX_AUDMUX_V1_PCR_RCLKDIR |
			IMX_AUDMUX_V1_PCR_TFCSEL(MX27_AUDMUX_HPCR3_SSI_PINS_4) |
			IMX_AUDMUX_V1_PCR_RFCSEL(MX27_AUDMUX_HPCR3_SSI_PINS_4) |
			IMX_AUDMUX_V1_PCR_RXDSEL(MX27_AUDMUX_HPCR3_SSI_PINS_4)
		);
		imx_audmux_v1_configure_port(MX27_AUDMUX_HPCR3_SSI_PINS_4,
			IMX_AUDMUX_V1_PCR_SYN |
			IMX_AUDMUX_V1_PCR_RXDSEL(MX27_AUDMUX_HPCR1_SSI0)
		);
	}

	return ret;
}