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
struct TYPE_4__ {int dsack_seen; } ;
struct TYPE_3__ {int /*<<< orphan*/  sack_ok; } ;
struct tcp_sock {int /*<<< orphan*/  dsack_dups; TYPE_2__ rack; TYPE_1__ rx_opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_DSACK_SEEN ; 

__attribute__((used)) static void tcp_dsack_seen(struct tcp_sock *tp)
{
	tp->rx_opt.sack_ok |= TCP_DSACK_SEEN;
	tp->rack.dsack_seen = 1;
	tp->dsack_dups++;
}