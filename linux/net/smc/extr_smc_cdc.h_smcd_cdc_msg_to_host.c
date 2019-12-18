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
union smc_host_cursor {int /*<<< orphan*/  count; int /*<<< orphan*/  wrap; } ;
struct TYPE_4__ {int /*<<< orphan*/  conn_state_flags; int /*<<< orphan*/  prod_flags; int /*<<< orphan*/  count; int /*<<< orphan*/  wrap; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; int /*<<< orphan*/  wrap; } ;
struct smcd_cdc_msg {TYPE_2__ cons; TYPE_1__ prod; } ;
struct smc_host_cdc_msg {int /*<<< orphan*/  conn_state_flags; int /*<<< orphan*/  prod_flags; int /*<<< orphan*/  cons; int /*<<< orphan*/  prod; } ;
struct smc_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  smc_curs_copy (int /*<<< orphan*/ *,union smc_host_cursor*,struct smc_connection*) ; 

__attribute__((used)) static inline void smcd_cdc_msg_to_host(struct smc_host_cdc_msg *local,
					struct smcd_cdc_msg *peer,
					struct smc_connection *conn)
{
	union smc_host_cursor temp;

	temp.wrap = peer->prod.wrap;
	temp.count = peer->prod.count;
	smc_curs_copy(&local->prod, &temp, conn);

	temp.wrap = peer->cons.wrap;
	temp.count = peer->cons.count;
	smc_curs_copy(&local->cons, &temp, conn);
	local->prod_flags = peer->cons.prod_flags;
	local->conn_state_flags = peer->cons.conn_state_flags;
}