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
struct at76_req_scan {void* probe_delay; void* max_channel_time; void* min_channel_time; scalar_t__ international_scan; int /*<<< orphan*/  scan_type; int /*<<< orphan*/  channel; int /*<<< orphan*/  bssid; } ;
struct at76_priv {int /*<<< orphan*/  udev; int /*<<< orphan*/  scan_max_time; int /*<<< orphan*/  scan_min_time; int /*<<< orphan*/  channel; } ;
typedef  int /*<<< orphan*/  scan ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SCAN ; 
 int /*<<< orphan*/  SCAN_TYPE_PASSIVE ; 
 int at76_get_cmd_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int at76_set_card_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct at76_req_scan*,int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct at76_req_scan*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int at76_start_monitor(struct at76_priv *priv)
{
	struct at76_req_scan scan;
	int ret;

	memset(&scan, 0, sizeof(struct at76_req_scan));
	eth_broadcast_addr(scan.bssid);

	scan.channel = priv->channel;
	scan.scan_type = SCAN_TYPE_PASSIVE;
	scan.international_scan = 0;
	scan.min_channel_time = cpu_to_le16(priv->scan_min_time);
	scan.max_channel_time = cpu_to_le16(priv->scan_max_time);
	scan.probe_delay = cpu_to_le16(0);

	ret = at76_set_card_command(priv->udev, CMD_SCAN, &scan, sizeof(scan));
	if (ret >= 0)
		ret = at76_get_cmd_status(priv->udev, CMD_SCAN);

	return ret;
}