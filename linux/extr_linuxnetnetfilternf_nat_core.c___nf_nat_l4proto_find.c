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
struct nf_nat_l4proto {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** nf_nat_l4protos ; 
 struct nf_nat_l4proto const* rcu_dereference (int /*<<< orphan*/ ) ; 

inline const struct nf_nat_l4proto *
__nf_nat_l4proto_find(u8 family, u8 protonum)
{
	return rcu_dereference(nf_nat_l4protos[family][protonum]);
}