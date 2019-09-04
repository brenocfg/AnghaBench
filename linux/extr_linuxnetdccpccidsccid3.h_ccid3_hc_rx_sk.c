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
struct ccid3_hc_rx_sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dccps_hc_rx_ccid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct ccid3_hc_rx_sock* ccid_priv (int /*<<< orphan*/ ) ; 
 TYPE_1__* dccp_sk (struct sock const*) ; 

__attribute__((used)) static inline struct ccid3_hc_rx_sock *ccid3_hc_rx_sk(const struct sock *sk)
{
	struct ccid3_hc_rx_sock *hcrx = ccid_priv(dccp_sk(sk)->dccps_hc_rx_ccid);
	BUG_ON(hcrx == NULL);
	return hcrx;
}