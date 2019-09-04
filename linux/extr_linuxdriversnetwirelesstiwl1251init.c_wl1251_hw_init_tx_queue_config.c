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
struct wl1251_acx_mem_map {int /*<<< orphan*/  num_tx_mem_blocks; } ;
struct wl1251 {struct wl1251_acx_mem_map* target_mem_map; } ;
struct acx_tx_queue_qos_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_TX_QUEUE_CFG ; 
 int /*<<< orphan*/  AC_BE ; 
 int /*<<< orphan*/  AC_BK ; 
 int /*<<< orphan*/  AC_VI ; 
 int /*<<< orphan*/  AC_VO ; 
 int /*<<< orphan*/  AIFS_DIFS ; 
 int /*<<< orphan*/  CWMAX_BE ; 
 int /*<<< orphan*/  CWMAX_BK ; 
 int /*<<< orphan*/  CWMAX_VI ; 
 int /*<<< orphan*/  CWMAX_VO ; 
 int /*<<< orphan*/  CWMIN_BE ; 
 int /*<<< orphan*/  CWMIN_BK ; 
 int /*<<< orphan*/  CWMIN_VI ; 
 int /*<<< orphan*/  CWMIN_VO ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_NUM_OF_AC ; 
 int /*<<< orphan*/  TXOP_BE ; 
 int /*<<< orphan*/  TXOP_BK ; 
 int /*<<< orphan*/  TXOP_VI ; 
 int /*<<< orphan*/  TXOP_VO ; 
 int /*<<< orphan*/  kfree (struct acx_tx_queue_qos_config*) ; 
 struct acx_tx_queue_qos_config* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_acx_ac_cfg (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_tx_queue_qos_config*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int wl1251_hw_init_txq_fill (int,struct acx_tx_queue_qos_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl1251_hw_init_tx_queue_config(struct wl1251 *wl)
{
	struct acx_tx_queue_qos_config *config;
	struct wl1251_acx_mem_map *wl_mem_map = wl->target_mem_map;
	int ret, i;

	wl1251_debug(DEBUG_ACX, "acx tx queue config");

	config = kzalloc(sizeof(*config), GFP_KERNEL);
	if (!config) {
		ret = -ENOMEM;
		goto out;
	}

	for (i = 0; i < MAX_NUM_OF_AC; i++) {
		ret = wl1251_hw_init_txq_fill(i, config,
					      wl_mem_map->num_tx_mem_blocks);
		if (ret < 0)
			goto out;

		ret = wl1251_cmd_configure(wl, ACX_TX_QUEUE_CFG,
					   config, sizeof(*config));
		if (ret < 0)
			goto out;
	}

	wl1251_acx_ac_cfg(wl, AC_BE, CWMIN_BE, CWMAX_BE, AIFS_DIFS, TXOP_BE);
	wl1251_acx_ac_cfg(wl, AC_BK, CWMIN_BK, CWMAX_BK, AIFS_DIFS, TXOP_BK);
	wl1251_acx_ac_cfg(wl, AC_VI, CWMIN_VI, CWMAX_VI, AIFS_DIFS, TXOP_VI);
	wl1251_acx_ac_cfg(wl, AC_VO, CWMIN_VO, CWMAX_VO, AIFS_DIFS, TXOP_VO);

out:
	kfree(config);
	return ret;
}