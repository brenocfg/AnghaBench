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
typedef  union smc_host_cursor {int dummy; } smc_host_cursor ;
struct TYPE_2__ {int /*<<< orphan*/  cons; } ;
struct smc_connection {TYPE_1__ local_tx_ctrl; } ;
struct smc_sock {struct smc_connection conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  smc_curs_copy (union smc_host_cursor*,int /*<<< orphan*/ *,struct smc_connection*) ; 
 int /*<<< orphan*/  smc_rx_update_consumer (struct smc_sock*,union smc_host_cursor,size_t) ; 

__attribute__((used)) static void smc_rx_update_cons(struct smc_sock *smc, size_t len)
{
	struct smc_connection *conn = &smc->conn;
	union smc_host_cursor cons;

	smc_curs_copy(&cons, &conn->local_tx_ctrl.cons, conn);
	smc_rx_update_consumer(smc, cons, len);
}