#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {struct device_node* of_node; } ;
struct platform_device {TYPE_8__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_13__ {TYPE_3__* codecs; TYPE_2__* platforms; TYPE_1__* cpus; } ;
struct TYPE_12__ {char* name; TYPE_8__* dev; } ;
struct TYPE_11__ {char* name; struct device_node* of_node; } ;
struct TYPE_10__ {char* name; struct device_node* of_node; } ;
struct TYPE_9__ {char* dai_name; struct device_node* of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int IMX_AUDMUX_V1_PCR_RCLKDIR ; 
 int IMX_AUDMUX_V1_PCR_RFCSEL (int /*<<< orphan*/ ) ; 
 int IMX_AUDMUX_V1_PCR_RFSDIR ; 
 int IMX_AUDMUX_V1_PCR_RXDSEL (int /*<<< orphan*/ ) ; 
 int IMX_AUDMUX_V1_PCR_SYN ; 
 int IMX_AUDMUX_V1_PCR_TCLKDIR ; 
 int IMX_AUDMUX_V1_PCR_TFCSEL (int /*<<< orphan*/ ) ; 
 int IMX_AUDMUX_V1_PCR_TFSDIR ; 
 int /*<<< orphan*/  IMX_AUDMUX_V2_PDCR_RXDSEL (int) ; 
 int IMX_AUDMUX_V2_PTCR_SYN ; 
 int IMX_AUDMUX_V2_PTCR_TCLKDIR ; 
 int IMX_AUDMUX_V2_PTCR_TCSEL (int) ; 
 int IMX_AUDMUX_V2_PTCR_TFSDIR ; 
 int IMX_AUDMUX_V2_PTCR_TFSEL (int) ; 
 int /*<<< orphan*/  MX27_AUDMUX_HPCR1_SSI0 ; 
 int /*<<< orphan*/  MX27_AUDMUX_HPCR3_SSI_PINS_4 ; 
 int /*<<< orphan*/  dev_err (TYPE_8__*,char*,...) ; 
 TYPE_4__ eukrea_tlv320 ; 
 TYPE_6__ eukrea_tlv320_dai ; 
 int /*<<< orphan*/  imx_audmux_v1_configure_port (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imx_audmux_v2_configure_port (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ machine_is_eukrea_cpuimx25sd () ; 
 scalar_t__ machine_is_eukrea_cpuimx27 () ; 
 scalar_t__ machine_is_eukrea_cpuimx35sd () ; 
 scalar_t__ machine_is_eukrea_cpuimx51sd () ; 
 scalar_t__ of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int snd_soc_of_parse_card_name (TYPE_4__*,char*) ; 
 int snd_soc_register_card (TYPE_4__*) ; 

__attribute__((used)) static int eukrea_tlv320_probe(struct platform_device *pdev)
{
	int ret;
	int int_port = 0, ext_port;
	struct device_node *np = pdev->dev.of_node;
	struct device_node *ssi_np = NULL, *codec_np = NULL;

	eukrea_tlv320.dev = &pdev->dev;
	if (np) {
		ret = snd_soc_of_parse_card_name(&eukrea_tlv320,
						 "eukrea,model");
		if (ret) {
			dev_err(&pdev->dev,
				"eukrea,model node missing or invalid.\n");
			goto err;
		}

		ssi_np = of_parse_phandle(pdev->dev.of_node,
					  "ssi-controller", 0);
		if (!ssi_np) {
			dev_err(&pdev->dev,
				"ssi-controller missing or invalid.\n");
			ret = -ENODEV;
			goto err;
		}

		codec_np = of_parse_phandle(ssi_np, "codec-handle", 0);
		if (codec_np)
			eukrea_tlv320_dai.codecs->of_node = codec_np;
		else
			dev_err(&pdev->dev, "codec-handle node missing or invalid.\n");

		ret = of_property_read_u32(np, "fsl,mux-int-port", &int_port);
		if (ret) {
			dev_err(&pdev->dev,
				"fsl,mux-int-port node missing or invalid.\n");
			goto err;
		}
		ret = of_property_read_u32(np, "fsl,mux-ext-port", &ext_port);
		if (ret) {
			dev_err(&pdev->dev,
				"fsl,mux-ext-port node missing or invalid.\n");
			goto err;
		}

		/*
		 * The port numbering in the hardware manual starts at 1, while
		 * the audmux API expects it starts at 0.
		 */
		int_port--;
		ext_port--;

		eukrea_tlv320_dai.cpus->of_node = ssi_np;
		eukrea_tlv320_dai.platforms->of_node = ssi_np;
	} else {
		eukrea_tlv320_dai.cpus->dai_name = "imx-ssi.0";
		eukrea_tlv320_dai.platforms->name = "imx-ssi.0";
		eukrea_tlv320_dai.codecs->name = "tlv320aic23-codec.0-001a";
		eukrea_tlv320.name = "cpuimx-audio";
	}

	if (machine_is_eukrea_cpuimx27() ||
	    of_find_compatible_node(NULL, NULL, "fsl,imx21-audmux")) {
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
	} else if (machine_is_eukrea_cpuimx25sd() ||
		   machine_is_eukrea_cpuimx35sd() ||
		   machine_is_eukrea_cpuimx51sd() ||
		   of_find_compatible_node(NULL, NULL, "fsl,imx31-audmux")) {
		if (!np)
			ext_port = machine_is_eukrea_cpuimx25sd() ?
				4 : 3;

		imx_audmux_v2_configure_port(int_port,
			IMX_AUDMUX_V2_PTCR_SYN |
			IMX_AUDMUX_V2_PTCR_TFSDIR |
			IMX_AUDMUX_V2_PTCR_TFSEL(ext_port) |
			IMX_AUDMUX_V2_PTCR_TCLKDIR |
			IMX_AUDMUX_V2_PTCR_TCSEL(ext_port),
			IMX_AUDMUX_V2_PDCR_RXDSEL(ext_port)
		);
		imx_audmux_v2_configure_port(ext_port,
			IMX_AUDMUX_V2_PTCR_SYN,
			IMX_AUDMUX_V2_PDCR_RXDSEL(int_port)
		);
	} else {
		if (np) {
			/* The eukrea,asoc-tlv320 driver was explicitly
			 * requested (through the device tree).
			 */
			dev_err(&pdev->dev,
				"Missing or invalid audmux DT node.\n");
			return -ENODEV;
		} else {
			/* Return happy.
			 * We might run on a totally different machine.
			 */
			return 0;
		}
	}

	ret = snd_soc_register_card(&eukrea_tlv320);
err:
	if (ret)
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", ret);
	of_node_put(ssi_np);

	return ret;
}