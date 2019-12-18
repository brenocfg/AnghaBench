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
struct smc_connection {scalar_t__ urg_state; } ;
struct smc_sock {struct smc_connection conn; } ;

/* Variables and functions */
 scalar_t__ SMC_URG_VALID ; 
 scalar_t__ smc_rx_data_available (struct smc_connection*) ; 
 int /*<<< orphan*/  smc_rx_update_cons (struct smc_sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool smc_rx_recvmsg_data_available(struct smc_sock *smc)
{
	struct smc_connection *conn = &smc->conn;

	if (smc_rx_data_available(conn))
		return true;
	else if (conn->urg_state == SMC_URG_VALID)
		/* we received a single urgent Byte - skip */
		smc_rx_update_cons(smc, 0);
	return false;
}