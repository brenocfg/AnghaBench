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
typedef  int /*<<< orphan*/  u64 ;
struct rds_ib_connection {int /*<<< orphan*/  i_ack_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_ACK_REQUESTED ; 
 int /*<<< orphan*/  rds_ib_get_ack (struct rds_ib_connection*) ; 
 int /*<<< orphan*/  rds_ib_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_ib_ack_send_piggybacked ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u64 rds_ib_piggyb_ack(struct rds_ib_connection *ic)
{
	if (test_and_clear_bit(IB_ACK_REQUESTED, &ic->i_ack_flags))
		rds_ib_stats_inc(s_ib_ack_send_piggybacked);
	return rds_ib_get_ack(ic);
}