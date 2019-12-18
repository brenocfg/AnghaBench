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
struct sock {int dummy; } ;
struct rds_sock {int rs_rcv_bytes; int rs_congested; int /*<<< orphan*/  rs_bound_port; int /*<<< orphan*/  rs_bound_addr; TYPE_1__* rs_transport; } ;
struct rds_cong_map {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {scalar_t__ t_type; } ;

/* Variables and functions */
 scalar_t__ RDS_TRANS_LOOP ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_cong_clear_bit (struct rds_cong_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_cong_queue_updates (struct rds_cong_map*) ; 
 int /*<<< orphan*/  rds_cong_set_bit (struct rds_cong_map*,int /*<<< orphan*/ ) ; 
 int rds_sk_rcvbuf (struct rds_sock*) ; 
 int /*<<< orphan*/  rds_stats_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  s_recv_bytes_added_to_socket ; 
 int /*<<< orphan*/  s_recv_bytes_removed_from_socket ; 

__attribute__((used)) static void rds_recv_rcvbuf_delta(struct rds_sock *rs, struct sock *sk,
				  struct rds_cong_map *map,
				  int delta, __be16 port)
{
	int now_congested;

	if (delta == 0)
		return;

	rs->rs_rcv_bytes += delta;
	if (delta > 0)
		rds_stats_add(s_recv_bytes_added_to_socket, delta);
	else
		rds_stats_add(s_recv_bytes_removed_from_socket, -delta);

	/* loop transport doesn't send/recv congestion updates */
	if (rs->rs_transport->t_type == RDS_TRANS_LOOP)
		return;

	now_congested = rs->rs_rcv_bytes > rds_sk_rcvbuf(rs);

	rdsdebug("rs %p (%pI6c:%u) recv bytes %d buf %d "
	  "now_cong %d delta %d\n",
	  rs, &rs->rs_bound_addr,
	  ntohs(rs->rs_bound_port), rs->rs_rcv_bytes,
	  rds_sk_rcvbuf(rs), now_congested, delta);

	/* wasn't -> am congested */
	if (!rs->rs_congested && now_congested) {
		rs->rs_congested = 1;
		rds_cong_set_bit(map, port);
		rds_cong_queue_updates(map);
	}
	/* was -> aren't congested */
	/* Require more free space before reporting uncongested to prevent
	   bouncing cong/uncong state too often */
	else if (rs->rs_congested && (rs->rs_rcv_bytes < (rds_sk_rcvbuf(rs)/2))) {
		rs->rs_congested = 0;
		rds_cong_clear_bit(map, port);
		rds_cong_queue_updates(map);
	}

	/* do nothing if no change in cong state */
}