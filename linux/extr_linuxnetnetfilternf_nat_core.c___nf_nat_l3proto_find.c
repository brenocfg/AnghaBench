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
typedef  size_t u8 ;
struct nf_nat_l3proto {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * nf_nat_l3protos ; 
 struct nf_nat_l3proto const* rcu_dereference (int /*<<< orphan*/ ) ; 

inline const struct nf_nat_l3proto *
__nf_nat_l3proto_find(u8 family)
{
	return rcu_dereference(nf_nat_l3protos[family]);
}