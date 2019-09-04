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
struct xdp_sock {TYPE_1__* umem; TYPE_1__* rx; } ;
struct TYPE_2__ {struct TYPE_2__* fq; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (TYPE_1__*) ; 

bool xsk_is_setup_for_bpf_map(struct xdp_sock *xs)
{
	return READ_ONCE(xs->rx) &&  READ_ONCE(xs->umem) &&
		READ_ONCE(xs->umem->fq);
}