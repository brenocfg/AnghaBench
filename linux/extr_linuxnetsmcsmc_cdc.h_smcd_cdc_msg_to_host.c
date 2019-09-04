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
struct smcd_cdc_msg {int /*<<< orphan*/  conn_state_flags; int /*<<< orphan*/  prod_flags; int /*<<< orphan*/  cons_count; int /*<<< orphan*/  cons_wrap; int /*<<< orphan*/  prod_count; int /*<<< orphan*/  prod_wrap; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; int /*<<< orphan*/  wrap; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; int /*<<< orphan*/  wrap; } ;
struct smc_host_cdc_msg {int /*<<< orphan*/  conn_state_flags; int /*<<< orphan*/  prod_flags; TYPE_2__ cons; TYPE_1__ prod; } ;

/* Variables and functions */

__attribute__((used)) static inline void smcd_cdc_msg_to_host(struct smc_host_cdc_msg *local,
					struct smcd_cdc_msg *peer)
{
	local->prod.wrap = peer->prod_wrap;
	local->prod.count = peer->prod_count;
	local->cons.wrap = peer->cons_wrap;
	local->cons.count = peer->cons_count;
	local->prod_flags = peer->prod_flags;
	local->conn_state_flags = peer->conn_state_flags;
}