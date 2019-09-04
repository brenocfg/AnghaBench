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
struct zfcp_adapter {scalar_t__ next_port_scan; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_scan_ratelimit ; 
 int /*<<< orphan*/  zfcp_fc_port_scan_backoff () ; 

__attribute__((used)) static void zfcp_fc_port_scan_time(struct zfcp_adapter *adapter)
{
	unsigned long interval = msecs_to_jiffies(port_scan_ratelimit);
	unsigned long backoff = msecs_to_jiffies(zfcp_fc_port_scan_backoff());

	adapter->next_port_scan = jiffies + interval + backoff;
}