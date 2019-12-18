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
struct TYPE_2__ {int /*<<< orphan*/ * dccps_hc_rx_ackvec; } ;

/* Variables and functions */
 int /*<<< orphan*/  dccp_ackvec_is_empty (int /*<<< orphan*/ *) ; 
 TYPE_1__* dccp_sk (struct sock const*) ; 

__attribute__((used)) static inline int dccp_ackvec_pending(const struct sock *sk)
{
	return dccp_sk(sk)->dccps_hc_rx_ackvec != NULL &&
	       !dccp_ackvec_is_empty(dccp_sk(sk)->dccps_hc_rx_ackvec);
}