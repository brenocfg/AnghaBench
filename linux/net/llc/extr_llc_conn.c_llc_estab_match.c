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
struct sock {int dummy; } ;
struct TYPE_4__ {scalar_t__ lsap; int /*<<< orphan*/  mac; } ;
struct TYPE_3__ {scalar_t__ lsap; int /*<<< orphan*/  mac; } ;
struct llc_sock {TYPE_2__ daddr; TYPE_1__ laddr; } ;
struct llc_sap {int dummy; } ;
struct llc_addr {scalar_t__ lsap; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct llc_sock* llc_sk (struct sock const*) ; 

__attribute__((used)) static inline bool llc_estab_match(const struct llc_sap *sap,
				   const struct llc_addr *daddr,
				   const struct llc_addr *laddr,
				   const struct sock *sk)
{
	struct llc_sock *llc = llc_sk(sk);

	return llc->laddr.lsap == laddr->lsap &&
		llc->daddr.lsap == daddr->lsap &&
		ether_addr_equal(llc->laddr.mac, laddr->mac) &&
		ether_addr_equal(llc->daddr.mac, daddr->mac);
}