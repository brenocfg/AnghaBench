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
struct TYPE_2__ {void* o2net_reconnect_delay_ms; void* o2net_keepalive_delay_ms; void* o2net_idle_timeout_ms; void* o2hb_heartbeat_timeout_ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  O2HB_MAX_WRITE_TIMEOUT_MS ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 TYPE_1__* o2net_hand ; 
 int /*<<< orphan*/  o2net_idle_timeout () ; 
 int /*<<< orphan*/  o2net_keepalive_delay () ; 
 int /*<<< orphan*/  o2net_reconnect_delay () ; 

__attribute__((used)) static void o2net_initialize_handshake(void)
{
	o2net_hand->o2hb_heartbeat_timeout_ms = cpu_to_be32(
		O2HB_MAX_WRITE_TIMEOUT_MS);
	o2net_hand->o2net_idle_timeout_ms = cpu_to_be32(o2net_idle_timeout());
	o2net_hand->o2net_keepalive_delay_ms = cpu_to_be32(
		o2net_keepalive_delay());
	o2net_hand->o2net_reconnect_delay_ms = cpu_to_be32(
		o2net_reconnect_delay());
}