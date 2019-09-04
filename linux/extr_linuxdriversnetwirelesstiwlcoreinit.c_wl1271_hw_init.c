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
struct wl1271 {int /*<<< orphan*/ * target_mem_map; TYPE_3__* hw; TYPE_1__* ops; } ;
struct TYPE_6__ {TYPE_2__* wiphy; } ;
struct TYPE_5__ {int /*<<< orphan*/  frag_threshold; } ;
struct TYPE_4__ {int (* hw_init ) (struct wl1271*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int stub1 (struct wl1271*) ; 
 int wl1271_acx_dco_itrim_params (struct wl1271*) ; 
 int wl1271_acx_frag_threshold (struct wl1271*,int /*<<< orphan*/ ) ; 
 int wl1271_acx_init_mem_config (struct wl1271*) ; 
 int wl1271_acx_init_rx_interrupt (struct wl1271*) ; 
 int wl1271_acx_pm_config (struct wl1271*) ; 
 int wl1271_acx_tx_config_options (struct wl1271*) ; 
 int wl1271_cmd_data_path (struct wl1271*,int) ; 
 int wl1271_init_energy_detection (struct wl1271*) ; 
 int wl1271_init_pta (struct wl1271*) ; 
 int wl1271_init_templates_config (struct wl1271*) ; 
 int wl12xx_acx_config_hangover (struct wl1271*) ; 
 int wl12xx_acx_mem_cfg (struct wl1271*) ; 
 int wl12xx_acx_set_rate_mgmt_params (struct wl1271*) ; 
 int wl12xx_init_fwlog (struct wl1271*) ; 
 int wl12xx_init_rx_config (struct wl1271*) ; 
 int wlcore_cmd_regdomain_config_locked (struct wl1271*) ; 

int wl1271_hw_init(struct wl1271 *wl)
{
	int ret;

	/* Chip-specific hw init */
	ret = wl->ops->hw_init(wl);
	if (ret < 0)
		return ret;

	/* Init templates */
	ret = wl1271_init_templates_config(wl);
	if (ret < 0)
		return ret;

	ret = wl12xx_acx_mem_cfg(wl);
	if (ret < 0)
		return ret;

	/* Configure the FW logger */
	ret = wl12xx_init_fwlog(wl);
	if (ret < 0)
		return ret;

	ret = wlcore_cmd_regdomain_config_locked(wl);
	if (ret < 0)
		return ret;

	/* Bluetooth WLAN coexistence */
	ret = wl1271_init_pta(wl);
	if (ret < 0)
		return ret;

	/* Default memory configuration */
	ret = wl1271_acx_init_mem_config(wl);
	if (ret < 0)
		return ret;

	/* RX config */
	ret = wl12xx_init_rx_config(wl);
	if (ret < 0)
		goto out_free_memmap;

	ret = wl1271_acx_dco_itrim_params(wl);
	if (ret < 0)
		goto out_free_memmap;

	/* Configure TX patch complete interrupt behavior */
	ret = wl1271_acx_tx_config_options(wl);
	if (ret < 0)
		goto out_free_memmap;

	/* RX complete interrupt pacing */
	ret = wl1271_acx_init_rx_interrupt(wl);
	if (ret < 0)
		goto out_free_memmap;

	/* Energy detection */
	ret = wl1271_init_energy_detection(wl);
	if (ret < 0)
		goto out_free_memmap;

	/* Default fragmentation threshold */
	ret = wl1271_acx_frag_threshold(wl, wl->hw->wiphy->frag_threshold);
	if (ret < 0)
		goto out_free_memmap;

	/* Enable data path */
	ret = wl1271_cmd_data_path(wl, 1);
	if (ret < 0)
		goto out_free_memmap;

	/* configure PM */
	ret = wl1271_acx_pm_config(wl);
	if (ret < 0)
		goto out_free_memmap;

	ret = wl12xx_acx_set_rate_mgmt_params(wl);
	if (ret < 0)
		goto out_free_memmap;

	/* configure hangover */
	ret = wl12xx_acx_config_hangover(wl);
	if (ret < 0)
		goto out_free_memmap;

	return 0;

 out_free_memmap:
	kfree(wl->target_mem_map);
	wl->target_mem_map = NULL;

	return ret;
}