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
typedef  int __be32 ;
struct TYPE_4__ {size_t dccps_qpolicy; } ;
struct TYPE_3__ {int params; } ;

/* Variables and functions */
 TYPE_2__* dccp_sk (struct sock*) ; 
 TYPE_1__* qpol_table ; 

bool dccp_qpolicy_param_ok(struct sock *sk, __be32 param)
{
	/* check if exactly one bit is set */
	if (!param || (param & (param - 1)))
		return false;
	return (qpol_table[dccp_sk(sk)->dccps_qpolicy].params & param) == param;
}