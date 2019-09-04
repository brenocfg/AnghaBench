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
typedef  int /*<<< orphan*/  u8 ;
struct nf_nat_proto_clean {int /*<<< orphan*/  l4proto; int /*<<< orphan*/  l3proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_ct_iterate_destroy (int /*<<< orphan*/ ,struct nf_nat_proto_clean*) ; 
 int /*<<< orphan*/  nf_nat_proto_remove ; 

__attribute__((used)) static void nf_nat_l4proto_clean(u8 l3proto, u8 l4proto)
{
	struct nf_nat_proto_clean clean = {
		.l3proto = l3proto,
		.l4proto = l4proto,
	};

	nf_ct_iterate_destroy(nf_nat_proto_remove, &clean);
}