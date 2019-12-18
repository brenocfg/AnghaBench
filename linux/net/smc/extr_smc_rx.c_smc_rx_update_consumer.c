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
typedef  union smc_host_cursor {int dummy; } smc_host_cursor ;
struct sock {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cons; } ;
struct smc_connection {scalar_t__ urg_state; int urg_rx_skip_pend; TYPE_2__ local_tx_ctrl; TYPE_1__* rmb_desc; int /*<<< orphan*/  urg_curs; } ;
struct smc_sock {struct sock sk; struct smc_connection conn; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 void* SMC_URG_READ ; 
 scalar_t__ SMC_URG_VALID ; 
 int /*<<< orphan*/  SOCK_URGINLINE ; 
 int /*<<< orphan*/  smc_curs_add (int /*<<< orphan*/ ,union smc_host_cursor*,int) ; 
 int smc_curs_comp (int /*<<< orphan*/ ,union smc_host_cursor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_curs_copy (int /*<<< orphan*/ *,union smc_host_cursor*,struct smc_connection*) ; 
 int /*<<< orphan*/  smc_tx_consumer_update (struct smc_connection*,int) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_rx_update_consumer(struct smc_sock *smc,
				  union smc_host_cursor cons, size_t len)
{
	struct smc_connection *conn = &smc->conn;
	struct sock *sk = &smc->sk;
	bool force = false;
	int diff, rc = 0;

	smc_curs_add(conn->rmb_desc->len, &cons, len);

	/* did we process urgent data? */
	if (conn->urg_state == SMC_URG_VALID || conn->urg_rx_skip_pend) {
		diff = smc_curs_comp(conn->rmb_desc->len, &cons,
				     &conn->urg_curs);
		if (sock_flag(sk, SOCK_URGINLINE)) {
			if (diff == 0) {
				force = true;
				rc = 1;
				conn->urg_state = SMC_URG_READ;
			}
		} else {
			if (diff == 1) {
				/* skip urgent byte */
				force = true;
				smc_curs_add(conn->rmb_desc->len, &cons, 1);
				conn->urg_rx_skip_pend = false;
			} else if (diff < -1)
				/* we read past urgent byte */
				conn->urg_state = SMC_URG_READ;
		}
	}

	smc_curs_copy(&conn->local_tx_ctrl.cons, &cons, conn);

	/* send consumer cursor update if required */
	/* similar to advertising new TCP rcv_wnd if required */
	smc_tx_consumer_update(conn, force);

	return rc;
}