#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct of_device_id {scalar_t__ data; } ;
struct fsl_ssi {int has_ipg_clk_name; int synchronous; int use_dma; int fifo_depth; int use_dual_fifo; int /*<<< orphan*/  card_idx; int /*<<< orphan*/ * card_name; int /*<<< orphan*/  dai_fmt; scalar_t__ soc; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FSLSSI_AC97_DAIFMT ; 
 scalar_t__ IMX_DMATYPE_SSI_DUAL ; 
 int be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  fsl_ssi_ids ; 
 int /*<<< orphan*/  make_lowercase (int /*<<< orphan*/ *) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 int /*<<< orphan*/  of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 void* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_match_string (struct device_node*,char*,char*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32_array (struct device_node*,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int fsl_ssi_probe_from_dt(struct fsl_ssi *ssi)
{
	struct device *dev = ssi->dev;
	struct device_node *np = dev->of_node;
	const struct of_device_id *of_id;
	const char *p, *sprop;
	const __be32 *iprop;
	u32 dmas[4];
	int ret;

	of_id = of_match_device(fsl_ssi_ids, dev);
	if (!of_id || !of_id->data)
		return -EINVAL;

	ssi->soc = of_id->data;

	ret = of_property_match_string(np, "clock-names", "ipg");
	/* Get error code if not found */
	ssi->has_ipg_clk_name = ret >= 0;

	/* Check if being used in AC97 mode */
	sprop = of_get_property(np, "fsl,mode", NULL);
	if (sprop && !strcmp(sprop, "ac97-slave")) {
		ssi->dai_fmt = FSLSSI_AC97_DAIFMT;

		ret = of_property_read_u32(np, "cell-index", &ssi->card_idx);
		if (ret) {
			dev_err(dev, "failed to get SSI index property\n");
			return -EINVAL;
		}
		strcpy(ssi->card_name, "ac97-codec");
	} else if (!of_find_property(np, "fsl,ssi-asynchronous", NULL)) {
		/*
		 * In synchronous mode, STCK and STFS ports are used by RX
		 * as well. So the software should limit the sample rates,
		 * sample bits and channels to be symmetric.
		 *
		 * This is exclusive with FSLSSI_AC97_FORMATS as AC97 runs
		 * in the SSI synchronous mode however it does not have to
		 * limit symmetric sample rates and sample bits.
		 */
		ssi->synchronous = true;
	}

	/* Select DMA or FIQ */
	ssi->use_dma = !of_property_read_bool(np, "fsl,fiq-stream-filter");

	/* Fetch FIFO depth; Set to 8 for older DT without this property */
	iprop = of_get_property(np, "fsl,fifo-depth", NULL);
	if (iprop)
		ssi->fifo_depth = be32_to_cpup(iprop);
	else
		ssi->fifo_depth = 8;

	/* Use dual FIFO mode depending on the support from SDMA script */
	ret = of_property_read_u32_array(np, "dmas", dmas, 4);
	if (ssi->use_dma && !ret && dmas[2] == IMX_DMATYPE_SSI_DUAL)
		ssi->use_dual_fifo = true;

	/*
	 * Backward compatible for older bindings by manually triggering the
	 * machine driver's probe(). Use /compatible property, including the
	 * address of CPU DAI driver structure, as the name of machine driver
	 *
	 * If card_name is set by AC97 earlier, bypass here since it uses a
	 * different name to register the device.
	 */
	if (!ssi->card_name[0] && of_get_property(np, "codec-handle", NULL)) {
		struct device_node *root = of_find_node_by_path("/");

		sprop = of_get_property(root, "compatible", NULL);
		of_node_put(root);
		/* Strip "fsl," in the compatible name if applicable */
		p = strrchr(sprop, ',');
		if (p)
			sprop = p + 1;
		snprintf(ssi->card_name, sizeof(ssi->card_name),
			 "snd-soc-%s", sprop);
		make_lowercase(ssi->card_name);
		ssi->card_idx = 0;
	}

	return 0;
}