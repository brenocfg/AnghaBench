#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_6__ {struct davinci_mcasp_pdata* platform_data; struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_phandle_args {int /*<<< orphan*/ * args; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;
struct device_node {int dummy; } ;
struct davinci_mcasp_pdata {int op_mode; int tdm_slots; int num_serializer; int txnumevt; int rxnumevt; int sram_size_playback; int sram_size_capture; void* dismod; int /*<<< orphan*/  rx_dma_channel; int /*<<< orphan*/  tx_dma_channel; int /*<<< orphan*/ * serial_dir; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MCASP_DIT_MODE ; 
 void* DISMOD_LOW ; 
 void* DISMOD_VAL (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  be32_to_cpup (int const*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int) ; 
 struct davinci_mcasp_pdata* devm_kmemdup (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_dt_ids ; 
 int* of_get_property (struct device_node*,char*,int*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int,struct of_phandle_args*) ; 
 int of_property_match_string (struct device_node*,char*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static struct davinci_mcasp_pdata *davinci_mcasp_set_pdata_from_of(
						struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct davinci_mcasp_pdata *pdata = NULL;
	const struct of_device_id *match =
			of_match_device(mcasp_dt_ids, &pdev->dev);
	struct of_phandle_args dma_spec;

	const u32 *of_serial_dir32;
	u32 val;
	int i, ret = 0;

	if (pdev->dev.platform_data) {
		pdata = pdev->dev.platform_data;
		pdata->dismod = DISMOD_LOW;
		return pdata;
	} else if (match) {
		pdata = devm_kmemdup(&pdev->dev, match->data, sizeof(*pdata),
				     GFP_KERNEL);
		if (!pdata) {
			ret = -ENOMEM;
			return pdata;
		}
	} else {
		/* control shouldn't reach here. something is wrong */
		ret = -EINVAL;
		goto nodata;
	}

	ret = of_property_read_u32(np, "op-mode", &val);
	if (ret >= 0)
		pdata->op_mode = val;

	ret = of_property_read_u32(np, "tdm-slots", &val);
	if (ret >= 0) {
		if (val < 2 || val > 32) {
			dev_err(&pdev->dev,
				"tdm-slots must be in rage [2-32]\n");
			ret = -EINVAL;
			goto nodata;
		}

		pdata->tdm_slots = val;
	}

	of_serial_dir32 = of_get_property(np, "serial-dir", &val);
	val /= sizeof(u32);
	if (of_serial_dir32) {
		u8 *of_serial_dir = devm_kzalloc(&pdev->dev,
						 (sizeof(*of_serial_dir) * val),
						 GFP_KERNEL);
		if (!of_serial_dir) {
			ret = -ENOMEM;
			goto nodata;
		}

		for (i = 0; i < val; i++)
			of_serial_dir[i] = be32_to_cpup(&of_serial_dir32[i]);

		pdata->num_serializer = val;
		pdata->serial_dir = of_serial_dir;
	}

	ret = of_property_match_string(np, "dma-names", "tx");
	if (ret < 0)
		goto nodata;

	ret = of_parse_phandle_with_args(np, "dmas", "#dma-cells", ret,
					 &dma_spec);
	if (ret < 0)
		goto nodata;

	pdata->tx_dma_channel = dma_spec.args[0];

	/* RX is not valid in DIT mode */
	if (pdata->op_mode != DAVINCI_MCASP_DIT_MODE) {
		ret = of_property_match_string(np, "dma-names", "rx");
		if (ret < 0)
			goto nodata;

		ret = of_parse_phandle_with_args(np, "dmas", "#dma-cells", ret,
						 &dma_spec);
		if (ret < 0)
			goto nodata;

		pdata->rx_dma_channel = dma_spec.args[0];
	}

	ret = of_property_read_u32(np, "tx-num-evt", &val);
	if (ret >= 0)
		pdata->txnumevt = val;

	ret = of_property_read_u32(np, "rx-num-evt", &val);
	if (ret >= 0)
		pdata->rxnumevt = val;

	ret = of_property_read_u32(np, "sram-size-playback", &val);
	if (ret >= 0)
		pdata->sram_size_playback = val;

	ret = of_property_read_u32(np, "sram-size-capture", &val);
	if (ret >= 0)
		pdata->sram_size_capture = val;

	ret = of_property_read_u32(np, "dismod", &val);
	if (ret >= 0) {
		if (val == 0 || val == 2 || val == 3) {
			pdata->dismod = DISMOD_VAL(val);
		} else {
			dev_warn(&pdev->dev, "Invalid dismod value: %u\n", val);
			pdata->dismod = DISMOD_LOW;
		}
	} else {
		pdata->dismod = DISMOD_LOW;
	}

	return  pdata;

nodata:
	if (ret < 0) {
		dev_err(&pdev->dev, "Error populating platform data, err %d\n",
			ret);
		pdata = NULL;
	}
	return  pdata;
}