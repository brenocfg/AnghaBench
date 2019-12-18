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
struct nf_conntrack_l4proto {scalar_t__ (* can_early_drop ) (struct nf_conn const*) ;} ;
struct nf_conn {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_ASSURED_BIT ; 
 struct nf_conntrack_l4proto* nf_ct_l4proto_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_protonum (struct nf_conn const*) ; 
 scalar_t__ stub1 (struct nf_conn const*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool gc_worker_can_early_drop(const struct nf_conn *ct)
{
	const struct nf_conntrack_l4proto *l4proto;

	if (!test_bit(IPS_ASSURED_BIT, &ct->status))
		return true;

	l4proto = nf_ct_l4proto_find(nf_ct_protonum(ct));
	if (l4proto->can_early_drop && l4proto->can_early_drop(ct))
		return true;

	return false;
}