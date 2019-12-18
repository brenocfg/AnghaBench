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
struct fsl_asoc_card_priv {int dai_fmt; TYPE_1__* pdev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IMX_AUDMUX_V2_PDCR_RXDSEL (int) ; 
 int IMX_AUDMUX_V2_PTCR_RCLKDIR ; 
 int IMX_AUDMUX_V2_PTCR_RCSEL (int) ; 
 int IMX_AUDMUX_V2_PTCR_RFSDIR ; 
 int IMX_AUDMUX_V2_PTCR_RFSEL (int) ; 
 int IMX_AUDMUX_V2_PTCR_SYN ; 
 int IMX_AUDMUX_V2_PTCR_TCLKDIR ; 
 int IMX_AUDMUX_V2_PTCR_TCSEL (int) ; 
 int IMX_AUDMUX_V2_PTCR_TFSDIR ; 
 int IMX_AUDMUX_V2_PTCR_TFSEL (int) ; 
#define  SND_SOC_DAIFMT_CBM_CFM 131 
#define  SND_SOC_DAIFMT_CBM_CFS 130 
#define  SND_SOC_DAIFMT_CBS_CFM 129 
#define  SND_SOC_DAIFMT_CBS_CFS 128 
 int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ fsl_asoc_card_is_ac97 (struct fsl_asoc_card_priv*) ; 
 int imx_audmux_v2_configure_port (int,int,unsigned int) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int fsl_asoc_card_audmux_init(struct device_node *np,
				     struct fsl_asoc_card_priv *priv)
{
	struct device *dev = &priv->pdev->dev;
	u32 int_ptcr = 0, ext_ptcr = 0;
	int int_port, ext_port;
	int ret;

	ret = of_property_read_u32(np, "mux-int-port", &int_port);
	if (ret) {
		dev_err(dev, "mux-int-port missing or invalid\n");
		return ret;
	}
	ret = of_property_read_u32(np, "mux-ext-port", &ext_port);
	if (ret) {
		dev_err(dev, "mux-ext-port missing or invalid\n");
		return ret;
	}

	/*
	 * The port numbering in the hardware manual starts at 1, while
	 * the AUDMUX API expects it starts at 0.
	 */
	int_port--;
	ext_port--;

	/*
	 * Use asynchronous mode (6 wires) for all cases except AC97.
	 * If only 4 wires are needed, just set SSI into
	 * synchronous mode and enable 4 PADs in IOMUX.
	 */
	switch (priv->dai_fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		int_ptcr = IMX_AUDMUX_V2_PTCR_RFSEL(8 | ext_port) |
			   IMX_AUDMUX_V2_PTCR_RCSEL(8 | ext_port) |
			   IMX_AUDMUX_V2_PTCR_TFSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_TCSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_RFSDIR |
			   IMX_AUDMUX_V2_PTCR_RCLKDIR |
			   IMX_AUDMUX_V2_PTCR_TFSDIR |
			   IMX_AUDMUX_V2_PTCR_TCLKDIR;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		int_ptcr = IMX_AUDMUX_V2_PTCR_RCSEL(8 | ext_port) |
			   IMX_AUDMUX_V2_PTCR_TCSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_RCLKDIR |
			   IMX_AUDMUX_V2_PTCR_TCLKDIR;
		ext_ptcr = IMX_AUDMUX_V2_PTCR_RFSEL(8 | int_port) |
			   IMX_AUDMUX_V2_PTCR_TFSEL(int_port) |
			   IMX_AUDMUX_V2_PTCR_RFSDIR |
			   IMX_AUDMUX_V2_PTCR_TFSDIR;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		int_ptcr = IMX_AUDMUX_V2_PTCR_RFSEL(8 | ext_port) |
			   IMX_AUDMUX_V2_PTCR_TFSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_RFSDIR |
			   IMX_AUDMUX_V2_PTCR_TFSDIR;
		ext_ptcr = IMX_AUDMUX_V2_PTCR_RCSEL(8 | int_port) |
			   IMX_AUDMUX_V2_PTCR_TCSEL(int_port) |
			   IMX_AUDMUX_V2_PTCR_RCLKDIR |
			   IMX_AUDMUX_V2_PTCR_TCLKDIR;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		ext_ptcr = IMX_AUDMUX_V2_PTCR_RFSEL(8 | int_port) |
			   IMX_AUDMUX_V2_PTCR_RCSEL(8 | int_port) |
			   IMX_AUDMUX_V2_PTCR_TFSEL(int_port) |
			   IMX_AUDMUX_V2_PTCR_TCSEL(int_port) |
			   IMX_AUDMUX_V2_PTCR_RFSDIR |
			   IMX_AUDMUX_V2_PTCR_RCLKDIR |
			   IMX_AUDMUX_V2_PTCR_TFSDIR |
			   IMX_AUDMUX_V2_PTCR_TCLKDIR;
		break;
	default:
		if (!fsl_asoc_card_is_ac97(priv))
			return -EINVAL;
	}

	if (fsl_asoc_card_is_ac97(priv)) {
		int_ptcr = IMX_AUDMUX_V2_PTCR_SYN |
			   IMX_AUDMUX_V2_PTCR_TCSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_TCLKDIR;
		ext_ptcr = IMX_AUDMUX_V2_PTCR_SYN |
			   IMX_AUDMUX_V2_PTCR_TFSEL(int_port) |
			   IMX_AUDMUX_V2_PTCR_TFSDIR;
	}

	/* Asynchronous mode can not be set along with RCLKDIR */
	if (!fsl_asoc_card_is_ac97(priv)) {
		unsigned int pdcr =
				IMX_AUDMUX_V2_PDCR_RXDSEL(ext_port);

		ret = imx_audmux_v2_configure_port(int_port, 0,
						   pdcr);
		if (ret) {
			dev_err(dev, "audmux internal port setup failed\n");
			return ret;
		}
	}

	ret = imx_audmux_v2_configure_port(int_port, int_ptcr,
					   IMX_AUDMUX_V2_PDCR_RXDSEL(ext_port));
	if (ret) {
		dev_err(dev, "audmux internal port setup failed\n");
		return ret;
	}

	if (!fsl_asoc_card_is_ac97(priv)) {
		unsigned int pdcr =
				IMX_AUDMUX_V2_PDCR_RXDSEL(int_port);

		ret = imx_audmux_v2_configure_port(ext_port, 0,
						   pdcr);
		if (ret) {
			dev_err(dev, "audmux external port setup failed\n");
			return ret;
		}
	}

	ret = imx_audmux_v2_configure_port(ext_port, ext_ptcr,
					   IMX_AUDMUX_V2_PDCR_RXDSEL(int_port));
	if (ret) {
		dev_err(dev, "audmux external port setup failed\n");
		return ret;
	}

	return 0;
}