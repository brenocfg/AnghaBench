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
typedef  scalar_t__ u64 ;
struct sock {int dummy; } ;
struct TYPE_2__ {int dccps_send_ndp_count; } ;

/* Variables and functions */
 TYPE_1__* dccp_sk (struct sock*) ; 

__attribute__((used)) static int dccp_hdlr_ndp(struct sock *sk, u64 enable, bool rx)
{
	if (!rx)
		dccp_sk(sk)->dccps_send_ndp_count = (enable > 0);
	return 0;
}