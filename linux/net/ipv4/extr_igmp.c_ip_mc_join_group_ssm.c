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
struct sock {int dummy; } ;
struct ip_mreqn {int dummy; } ;

/* Variables and functions */
 int __ip_mc_join_group (struct sock*,struct ip_mreqn*,unsigned int) ; 

int ip_mc_join_group_ssm(struct sock *sk, struct ip_mreqn *imr,
			 unsigned int mode)
{
	return __ip_mc_join_group(sk, imr, mode);
}