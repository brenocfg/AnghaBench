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
struct atm_vcc {TYPE_1__* stats; } ;
struct TYPE_4__ {scalar_t__ sk_rcvbuf; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_drop; } ;

/* Variables and functions */
 int /*<<< orphan*/  atm_force_charge (struct atm_vcc*,int) ; 
 int /*<<< orphan*/  atm_return (struct atm_vcc*,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_2__* sk_atm (struct atm_vcc*) ; 

int atm_charge(struct atm_vcc *vcc, int truesize)
{
	atm_force_charge(vcc, truesize);
	if (atomic_read(&sk_atm(vcc)->sk_rmem_alloc) <= sk_atm(vcc)->sk_rcvbuf)
		return 1;
	atm_return(vcc, truesize);
	atomic_inc(&vcc->stats->rx_drop);
	return 0;
}