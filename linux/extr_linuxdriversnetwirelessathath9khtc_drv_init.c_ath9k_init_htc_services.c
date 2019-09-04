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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ath9k_htc_priv {int /*<<< orphan*/  dev; TYPE_1__* htc; int /*<<< orphan*/  data_vo_ep; int /*<<< orphan*/  data_vi_ep; int /*<<< orphan*/  data_bk_ep; int /*<<< orphan*/  data_be_ep; int /*<<< orphan*/  mgmt_ep; int /*<<< orphan*/  uapsd_ep; int /*<<< orphan*/  cab_ep; int /*<<< orphan*/  beacon_ep; int /*<<< orphan*/  wmi_cmd_ep; int /*<<< orphan*/  wmi; } ;
struct TYPE_3__ {int credits; } ;

/* Variables and functions */
 scalar_t__ IS_AR7010_DEVICE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_BEACON_SVC ; 
 int /*<<< orphan*/  WMI_CAB_SVC ; 
 int /*<<< orphan*/  WMI_DATA_BE_SVC ; 
 int /*<<< orphan*/  WMI_DATA_BK_SVC ; 
 int /*<<< orphan*/  WMI_DATA_VI_SVC ; 
 int /*<<< orphan*/  WMI_DATA_VO_SVC ; 
 int /*<<< orphan*/  WMI_MGMT_SVC ; 
 int /*<<< orphan*/  WMI_UAPSD_SVC ; 
 int /*<<< orphan*/  ath9k_htc_beaconep ; 
 int ath9k_htc_connect_svc (struct ath9k_htc_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_htc_txep ; 
 int ath9k_wmi_connect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int htc_init (TYPE_1__*) ; 

__attribute__((used)) static int ath9k_init_htc_services(struct ath9k_htc_priv *priv, u16 devid,
				   u32 drv_info)
{
	int ret;

	/* WMI CMD*/
	ret = ath9k_wmi_connect(priv->htc, priv->wmi, &priv->wmi_cmd_ep);
	if (ret)
		goto err;

	/* Beacon */
	ret = ath9k_htc_connect_svc(priv, WMI_BEACON_SVC, ath9k_htc_beaconep,
				    &priv->beacon_ep);
	if (ret)
		goto err;

	/* CAB */
	ret = ath9k_htc_connect_svc(priv, WMI_CAB_SVC, ath9k_htc_txep,
				    &priv->cab_ep);
	if (ret)
		goto err;


	/* UAPSD */
	ret = ath9k_htc_connect_svc(priv, WMI_UAPSD_SVC, ath9k_htc_txep,
				    &priv->uapsd_ep);
	if (ret)
		goto err;

	/* MGMT */
	ret = ath9k_htc_connect_svc(priv, WMI_MGMT_SVC, ath9k_htc_txep,
				    &priv->mgmt_ep);
	if (ret)
		goto err;

	/* DATA BE */
	ret = ath9k_htc_connect_svc(priv, WMI_DATA_BE_SVC, ath9k_htc_txep,
				    &priv->data_be_ep);
	if (ret)
		goto err;

	/* DATA BK */
	ret = ath9k_htc_connect_svc(priv, WMI_DATA_BK_SVC, ath9k_htc_txep,
				    &priv->data_bk_ep);
	if (ret)
		goto err;

	/* DATA VI */
	ret = ath9k_htc_connect_svc(priv, WMI_DATA_VI_SVC, ath9k_htc_txep,
				    &priv->data_vi_ep);
	if (ret)
		goto err;

	/* DATA VO */
	ret = ath9k_htc_connect_svc(priv, WMI_DATA_VO_SVC, ath9k_htc_txep,
				    &priv->data_vo_ep);
	if (ret)
		goto err;

	/*
	 * Setup required credits before initializing HTC.
	 * This is a bit hacky, but, since queuing is done in
	 * the HIF layer, shouldn't matter much.
	 */

	if (IS_AR7010_DEVICE(drv_info))
		priv->htc->credits = 45;
	else
		priv->htc->credits = 33;

	ret = htc_init(priv->htc);
	if (ret)
		goto err;

	dev_info(priv->dev, "ath9k_htc: HTC initialized with %d credits\n",
		 priv->htc->credits);

	return 0;

err:
	dev_err(priv->dev, "ath9k_htc: Unable to initialize HTC services\n");
	return ret;
}