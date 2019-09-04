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
struct net_device {int dummy; } ;
struct gelic_wl_info {scalar_t__ scan_stat; int /*<<< orphan*/  scan_done; } ;
struct gelic_port {int dummy; } ;
struct gelic_eurus_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GELIC_EURUS_CMD_DISASSOC ; 
 scalar_t__ GELIC_WL_SCAN_STAT_SCANNING ; 
 int /*<<< orphan*/  HZ ; 
 struct gelic_eurus_cmd* gelic_eurus_sync_cmd (struct gelic_wl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelic_wl_send_iwap_event (struct gelic_wl_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gelic_eurus_cmd*) ; 
 struct gelic_port* netdev_priv (struct net_device*) ; 
 struct gelic_wl_info* port_wl (struct gelic_port*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gelic_wl_disconnect(struct net_device *netdev)
{
	struct gelic_port *port = netdev_priv(netdev);
	struct gelic_wl_info *wl = port_wl(port);
	struct gelic_eurus_cmd *cmd;

	/*
	 * If scann process is running on chip,
	 * further requests will be rejected
	 */
	if (wl->scan_stat == GELIC_WL_SCAN_STAT_SCANNING)
		wait_for_completion_timeout(&wl->scan_done, HZ);

	cmd = gelic_eurus_sync_cmd(wl, GELIC_EURUS_CMD_DISASSOC, NULL, 0);
	kfree(cmd);
	gelic_wl_send_iwap_event(wl, NULL);
}