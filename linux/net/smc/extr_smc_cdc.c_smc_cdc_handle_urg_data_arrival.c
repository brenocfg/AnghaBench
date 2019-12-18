#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int count; } ;
struct TYPE_4__ {int /*<<< orphan*/  prod; } ;
struct smc_connection {int rx_off; char urg_rx_byte; TYPE_2__* rmb_desc; TYPE_3__ urg_curs; int /*<<< orphan*/  urg_state; TYPE_1__ local_rx_ctrl; } ;
struct smc_sock {int /*<<< orphan*/  sk; struct smc_connection conn; } ;
struct TYPE_5__ {int len; scalar_t__ cpu_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_URG_VALID ; 
 int /*<<< orphan*/  SOCK_URGINLINE ; 
 int /*<<< orphan*/  sk_send_sigurg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_curs_copy (TYPE_3__*,int /*<<< orphan*/ *,struct smc_connection*) ; 
 int /*<<< orphan*/  sock_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smc_cdc_handle_urg_data_arrival(struct smc_sock *smc,
					    int *diff_prod)
{
	struct smc_connection *conn = &smc->conn;
	char *base;

	/* new data included urgent business */
	smc_curs_copy(&conn->urg_curs, &conn->local_rx_ctrl.prod, conn);
	conn->urg_state = SMC_URG_VALID;
	if (!sock_flag(&smc->sk, SOCK_URGINLINE))
		/* we'll skip the urgent byte, so don't account for it */
		(*diff_prod)--;
	base = (char *)conn->rmb_desc->cpu_addr + conn->rx_off;
	if (conn->urg_curs.count)
		conn->urg_rx_byte = *(base + conn->urg_curs.count - 1);
	else
		conn->urg_rx_byte = *(base + conn->rmb_desc->len - 1);
	sk_send_sigurg(&smc->sk);
}