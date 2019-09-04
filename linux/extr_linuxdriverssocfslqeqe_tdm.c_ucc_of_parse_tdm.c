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
typedef  void* u32 ;
struct TYPE_2__ {void* tdm_num; void* tx_sync; void* rx_sync; } ;
struct ucc_tdm_info {TYPE_1__ uf_info; } ;
struct ucc_tdm {int tdm_framer_type; void* si_regs; void* siram; void* siram_entry_id; int /*<<< orphan*/  tdm_mode; void* tdm_port; void* rx_ts_mask; void* tx_ts_mask; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* QE_CLK_NONE ; 
 void* QE_RSYNC_PIN ; 
 void* QE_TSYNC_PIN ; 
 int /*<<< orphan*/  TDM_INTERNAL_LOOPBACK ; 
 int /*<<< orphan*/  TDM_NORMAL ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  devm_iounmap (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  memset_io (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int /*<<< orphan*/ ,void**) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 void* qe_clock_source (char const*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  set_si_param (struct ucc_tdm*,struct ucc_tdm_info*) ; 
 int set_tdm_framer (char const*) ; 

int ucc_of_parse_tdm(struct device_node *np, struct ucc_tdm *utdm,
		     struct ucc_tdm_info *ut_info)
{
	const char *sprop;
	int ret = 0;
	u32 val;
	struct resource *res;
	struct device_node *np2;
	static int siram_init_flag;
	struct platform_device *pdev;

	sprop = of_get_property(np, "fsl,rx-sync-clock", NULL);
	if (sprop) {
		ut_info->uf_info.rx_sync = qe_clock_source(sprop);
		if ((ut_info->uf_info.rx_sync < QE_CLK_NONE) ||
		    (ut_info->uf_info.rx_sync > QE_RSYNC_PIN)) {
			pr_err("QE-TDM: Invalid rx-sync-clock property\n");
			return -EINVAL;
		}
	} else {
		pr_err("QE-TDM: Invalid rx-sync-clock property\n");
		return -EINVAL;
	}

	sprop = of_get_property(np, "fsl,tx-sync-clock", NULL);
	if (sprop) {
		ut_info->uf_info.tx_sync = qe_clock_source(sprop);
		if ((ut_info->uf_info.tx_sync < QE_CLK_NONE) ||
		    (ut_info->uf_info.tx_sync > QE_TSYNC_PIN)) {
			pr_err("QE-TDM: Invalid tx-sync-clock property\n");
		return -EINVAL;
		}
	} else {
		pr_err("QE-TDM: Invalid tx-sync-clock property\n");
		return -EINVAL;
	}

	ret = of_property_read_u32_index(np, "fsl,tx-timeslot-mask", 0, &val);
	if (ret) {
		pr_err("QE-TDM: Invalid tx-timeslot-mask property\n");
		return -EINVAL;
	}
	utdm->tx_ts_mask = val;

	ret = of_property_read_u32_index(np, "fsl,rx-timeslot-mask", 0, &val);
	if (ret) {
		ret = -EINVAL;
		pr_err("QE-TDM: Invalid rx-timeslot-mask property\n");
		return ret;
	}
	utdm->rx_ts_mask = val;

	ret = of_property_read_u32_index(np, "fsl,tdm-id", 0, &val);
	if (ret) {
		ret = -EINVAL;
		pr_err("QE-TDM: No fsl,tdm-id property for this UCC\n");
		return ret;
	}
	utdm->tdm_port = val;
	ut_info->uf_info.tdm_num = utdm->tdm_port;

	if (of_property_read_bool(np, "fsl,tdm-internal-loopback"))
		utdm->tdm_mode = TDM_INTERNAL_LOOPBACK;
	else
		utdm->tdm_mode = TDM_NORMAL;

	sprop = of_get_property(np, "fsl,tdm-framer-type", NULL);
	if (!sprop) {
		ret = -EINVAL;
		pr_err("QE-TDM: No tdm-framer-type property for UCC\n");
		return ret;
	}
	ret = set_tdm_framer(sprop);
	if (ret < 0)
		return -EINVAL;
	utdm->tdm_framer_type = ret;

	ret = of_property_read_u32_index(np, "fsl,siram-entry-id", 0, &val);
	if (ret) {
		ret = -EINVAL;
		pr_err("QE-TDM: No siram entry id for UCC\n");
		return ret;
	}
	utdm->siram_entry_id = val;

	set_si_param(utdm, ut_info);

	np2 = of_find_compatible_node(NULL, NULL, "fsl,t1040-qe-si");
	if (!np2)
		return -EINVAL;

	pdev = of_find_device_by_node(np2);
	if (!pdev) {
		pr_err("%s: failed to lookup pdev\n", np2->name);
		of_node_put(np2);
		return -EINVAL;
	}

	of_node_put(np2);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	utdm->si_regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(utdm->si_regs)) {
		ret = PTR_ERR(utdm->si_regs);
		goto err_miss_siram_property;
	}

	np2 = of_find_compatible_node(NULL, NULL, "fsl,t1040-qe-siram");
	if (!np2) {
		ret = -EINVAL;
		goto err_miss_siram_property;
	}

	pdev = of_find_device_by_node(np2);
	if (!pdev) {
		ret = -EINVAL;
		pr_err("%s: failed to lookup pdev\n", np2->name);
		of_node_put(np2);
		goto err_miss_siram_property;
	}

	of_node_put(np2);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	utdm->siram = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(utdm->siram)) {
		ret = PTR_ERR(utdm->siram);
		goto err_miss_siram_property;
	}

	if (siram_init_flag == 0) {
		memset_io(utdm->siram, 0,  resource_size(res));
		siram_init_flag = 1;
	}

	return ret;

err_miss_siram_property:
	devm_iounmap(&pdev->dev, utdm->si_regs);
	return ret;
}