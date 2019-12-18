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
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct smc_host_cdc_msg {int /*<<< orphan*/  conn_state_flags; int /*<<< orphan*/  prod_flags; int /*<<< orphan*/  cons; int /*<<< orphan*/  prod; int /*<<< orphan*/  token; int /*<<< orphan*/  seqno; int /*<<< orphan*/  len; TYPE_1__ common; } ;
struct smc_connection {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct smc_cdc_msg {int /*<<< orphan*/  conn_state_flags; int /*<<< orphan*/  prod_flags; int /*<<< orphan*/  cons; int /*<<< orphan*/  prod; int /*<<< orphan*/  token; int /*<<< orphan*/  seqno; int /*<<< orphan*/  len; TYPE_2__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_cdc_cursor_to_host (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct smc_connection*) ; 

__attribute__((used)) static inline void smcr_cdc_msg_to_host(struct smc_host_cdc_msg *local,
					struct smc_cdc_msg *peer,
					struct smc_connection *conn)
{
	local->common.type = peer->common.type;
	local->len = peer->len;
	local->seqno = ntohs(peer->seqno);
	local->token = ntohl(peer->token);
	smc_cdc_cursor_to_host(&local->prod, &peer->prod, conn);
	smc_cdc_cursor_to_host(&local->cons, &peer->cons, conn);
	local->prod_flags = peer->prod_flags;
	local->conn_state_flags = peer->conn_state_flags;
}