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
struct rds_ib_connection {int /*<<< orphan*/  i_ack_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_ACK_IN_FLIGHT ; 
 int /*<<< orphan*/  IB_ACK_REQUESTED ; 
 int /*<<< orphan*/  RDS_MAX_ADV_CREDIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_send_ack (struct rds_ib_connection*,unsigned int) ; 
 int /*<<< orphan*/  rds_ib_send_grab_credits (struct rds_ib_connection*,int,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_ib_ack_send_delayed ; 
 int /*<<< orphan*/  s_ib_tx_throttle ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rds_ib_attempt_ack(struct rds_ib_connection *ic)
{
	unsigned int adv_credits;

	if (!test_bit(IB_ACK_REQUESTED, &ic->i_ack_flags))
		return;

	if (test_and_set_bit(IB_ACK_IN_FLIGHT, &ic->i_ack_flags)) {
		rds_ib_stats_inc(s_ib_ack_send_delayed);
		return;
	}

	/* Can we get a send credit? */
	if (!rds_ib_send_grab_credits(ic, 1, &adv_credits, 0, RDS_MAX_ADV_CREDIT)) {
		rds_ib_stats_inc(s_ib_tx_throttle);
		clear_bit(IB_ACK_IN_FLIGHT, &ic->i_ack_flags);
		return;
	}

	clear_bit(IB_ACK_REQUESTED, &ic->i_ack_flags);
	rds_ib_send_ack(ic, adv_credits);
}