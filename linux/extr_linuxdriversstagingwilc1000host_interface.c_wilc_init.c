#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wilc_vif {int /*<<< orphan*/  ndev; struct wilc* wilc; } ;
struct wilc {int vif_num; TYPE_1__** vif; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  curr_tx_rate; int /*<<< orphan*/  passive_scan_time; int /*<<< orphan*/  active_scan_time; int /*<<< orphan*/  scan_source; int /*<<< orphan*/  site_survey_enabled; } ;
struct host_if_drv {int driver_handler_id; int /*<<< orphan*/  cfg_values_lock; scalar_t__ p2p_timeout; TYPE_2__ cfg_values; int /*<<< orphan*/  hif_state; int /*<<< orphan*/  remain_on_ch_timer; int /*<<< orphan*/  connect_timer; int /*<<< orphan*/  scan_timer; } ;
struct TYPE_3__ {struct host_if_drv* hif_drv; struct net_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVE_SCAN_TIME ; 
 int /*<<< orphan*/  AUTORATE ; 
 int /*<<< orphan*/  DEFAULT_SCAN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HOST_IF_IDLE ; 
 int /*<<< orphan*/  PASSIVE_SCAN_TIME ; 
 int /*<<< orphan*/  SITE_SURVEY_OFF ; 
 scalar_t__ clients_count ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  get_periodic_rssi ; 
 int /*<<< orphan*/  hif_deinit_lock ; 
 int /*<<< orphan*/  hif_driver_comp ; 
 int /*<<< orphan*/  hif_workqueue ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct host_if_drv*) ; 
 struct host_if_drv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listen_timer_cb ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  periodic_rssi ; 
 struct wilc_vif* periodic_rssi_vif ; 
 int /*<<< orphan*/  timer_connect_cb ; 
 int /*<<< orphan*/  timer_scan_cb ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wilc_optaining_ip ; 

int wilc_init(struct net_device *dev, struct host_if_drv **hif_drv_handler)
{
	struct host_if_drv *hif_drv;
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc = vif->wilc;
	int i;

	hif_drv  = kzalloc(sizeof(*hif_drv), GFP_KERNEL);
	if (!hif_drv)
		return -ENOMEM;

	*hif_drv_handler = hif_drv;
	for (i = 0; i < wilc->vif_num; i++)
		if (dev == wilc->vif[i]->ndev) {
			wilc->vif[i]->hif_drv = hif_drv;
			hif_drv->driver_handler_id = i + 1;
			break;
		}

	wilc_optaining_ip = false;

	if (clients_count == 0) {
		init_completion(&hif_driver_comp);
		mutex_init(&hif_deinit_lock);
	}

	if (clients_count == 0) {
		hif_workqueue = create_singlethread_workqueue("WILC_wq");
		if (!hif_workqueue) {
			netdev_err(vif->ndev, "Failed to create workqueue\n");
			kfree(hif_drv);
			return -ENOMEM;
		}

		periodic_rssi_vif = vif;
		timer_setup(&periodic_rssi, get_periodic_rssi, 0);
		mod_timer(&periodic_rssi, jiffies + msecs_to_jiffies(5000));
	}

	timer_setup(&hif_drv->scan_timer, timer_scan_cb, 0);
	timer_setup(&hif_drv->connect_timer, timer_connect_cb, 0);
	timer_setup(&hif_drv->remain_on_ch_timer, listen_timer_cb, 0);

	mutex_init(&hif_drv->cfg_values_lock);
	mutex_lock(&hif_drv->cfg_values_lock);

	hif_drv->hif_state = HOST_IF_IDLE;
	hif_drv->cfg_values.site_survey_enabled = SITE_SURVEY_OFF;
	hif_drv->cfg_values.scan_source = DEFAULT_SCAN;
	hif_drv->cfg_values.active_scan_time = ACTIVE_SCAN_TIME;
	hif_drv->cfg_values.passive_scan_time = PASSIVE_SCAN_TIME;
	hif_drv->cfg_values.curr_tx_rate = AUTORATE;

	hif_drv->p2p_timeout = 0;

	mutex_unlock(&hif_drv->cfg_values_lock);

	clients_count++;

	return 0;
}