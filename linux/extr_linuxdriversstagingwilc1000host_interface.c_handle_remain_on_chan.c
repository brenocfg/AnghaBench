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
typedef  int u8 ;
struct wilc_vif {int /*<<< orphan*/  ndev; struct host_if_drv* hif_drv; } ;
struct wid {int size; int* val; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct remain_ch {int /*<<< orphan*/  duration; scalar_t__ ch; int /*<<< orphan*/  id; int /*<<< orphan*/  (* ready ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  expired; int /*<<< orphan*/  arg; } ;
struct TYPE_4__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* ready ) (int /*<<< orphan*/ ) ;scalar_t__ ch; int /*<<< orphan*/  id; int /*<<< orphan*/  expired; } ;
struct TYPE_3__ {scalar_t__ scan_result; } ;
struct host_if_drv {int remain_on_ch_pending; scalar_t__ hif_state; TYPE_2__ remain_on_ch; int /*<<< orphan*/  remain_on_ch_timer; struct wilc_vif* remain_on_ch_timer_vif; TYPE_1__ usr_scan_req; } ;
typedef  int s8 ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HOST_IF_WAITING_CONN_RESP ; 
 int /*<<< orphan*/  SET_CFG ; 
 int /*<<< orphan*/  WID_REMAIN_ON_CHAN ; 
 int /*<<< orphan*/  WID_STR ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int p2p_listen_state ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ wilc_connecting ; 
 int /*<<< orphan*/  wilc_get_vif_idx (struct wilc_vif*) ; 
 scalar_t__ wilc_optaining_ip ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_remain_on_chan(struct wilc_vif *vif,
				 struct remain_ch *hif_remain_ch)
{
	int result;
	u8 remain_on_chan_flag;
	struct wid wid;
	struct host_if_drv *hif_drv = vif->hif_drv;

	if (!hif_drv->remain_on_ch_pending) {
		hif_drv->remain_on_ch.arg = hif_remain_ch->arg;
		hif_drv->remain_on_ch.expired = hif_remain_ch->expired;
		hif_drv->remain_on_ch.ready = hif_remain_ch->ready;
		hif_drv->remain_on_ch.ch = hif_remain_ch->ch;
		hif_drv->remain_on_ch.id = hif_remain_ch->id;
	} else {
		hif_remain_ch->ch = hif_drv->remain_on_ch.ch;
	}

	if (hif_drv->usr_scan_req.scan_result) {
		hif_drv->remain_on_ch_pending = 1;
		result = -EBUSY;
		goto error;
	}
	if (hif_drv->hif_state == HOST_IF_WAITING_CONN_RESP) {
		result = -EBUSY;
		goto error;
	}

	if (wilc_optaining_ip || wilc_connecting) {
		result = -EBUSY;
		goto error;
	}

	remain_on_chan_flag = true;
	wid.id = WID_REMAIN_ON_CHAN;
	wid.type = WID_STR;
	wid.size = 2;
	wid.val = kmalloc(wid.size, GFP_KERNEL);
	if (!wid.val) {
		result = -ENOMEM;
		goto error;
	}

	wid.val[0] = remain_on_chan_flag;
	wid.val[1] = (s8)hif_remain_ch->ch;

	result = wilc_send_config_pkt(vif, SET_CFG, &wid, 1,
				      wilc_get_vif_idx(vif));
	kfree(wid.val);
	if (result != 0)
		netdev_err(vif->ndev, "Failed to set remain on channel\n");

error:
	p2p_listen_state = 1;
	hif_drv->remain_on_ch_timer_vif = vif;
	mod_timer(&hif_drv->remain_on_ch_timer,
		  jiffies + msecs_to_jiffies(hif_remain_ch->duration));

	if (hif_drv->remain_on_ch.ready)
		hif_drv->remain_on_ch.ready(hif_drv->remain_on_ch.arg);

	if (hif_drv->remain_on_ch_pending)
		hif_drv->remain_on_ch_pending = 0;

	return result;
}