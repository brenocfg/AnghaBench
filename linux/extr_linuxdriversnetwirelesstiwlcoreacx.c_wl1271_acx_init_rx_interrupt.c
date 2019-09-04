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
struct wl1271_acx_rx_config_opt {int /*<<< orphan*/  queue_type; void* mblk_threshold; void* timeout; void* threshold; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue_type; int /*<<< orphan*/  irq_blk_threshold; int /*<<< orphan*/  irq_timeout; int /*<<< orphan*/  irq_pkt_threshold; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;
struct wl1271 {TYPE_2__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_RX_CONFIG_OPT ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl1271_acx_rx_config_opt*) ; 
 struct wl1271_acx_rx_config_opt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_acx_rx_config_opt*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_init_rx_interrupt(struct wl1271 *wl)
{
	struct wl1271_acx_rx_config_opt *rx_conf;
	int ret;

	wl1271_debug(DEBUG_ACX, "wl1271 rx interrupt config");

	rx_conf = kzalloc(sizeof(*rx_conf), GFP_KERNEL);
	if (!rx_conf) {
		ret = -ENOMEM;
		goto out;
	}

	rx_conf->threshold = cpu_to_le16(wl->conf.rx.irq_pkt_threshold);
	rx_conf->timeout = cpu_to_le16(wl->conf.rx.irq_timeout);
	rx_conf->mblk_threshold = cpu_to_le16(wl->conf.rx.irq_blk_threshold);
	rx_conf->queue_type = wl->conf.rx.queue_type;

	ret = wl1271_cmd_configure(wl, ACX_RX_CONFIG_OPT, rx_conf,
				   sizeof(*rx_conf));
	if (ret < 0) {
		wl1271_warning("wl1271 rx config opt failed: %d", ret);
		goto out;
	}

out:
	kfree(rx_conf);
	return ret;
}