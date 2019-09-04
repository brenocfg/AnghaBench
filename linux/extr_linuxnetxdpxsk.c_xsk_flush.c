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
struct TYPE_2__ {int /*<<< orphan*/  (* sk_data_ready ) (TYPE_1__*) ;} ;
struct xdp_sock {TYPE_1__ sk; int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  xskq_produce_flush_desc (int /*<<< orphan*/ ) ; 

void xsk_flush(struct xdp_sock *xs)
{
	xskq_produce_flush_desc(xs->rx);
	xs->sk.sk_data_ready(&xs->sk);
}