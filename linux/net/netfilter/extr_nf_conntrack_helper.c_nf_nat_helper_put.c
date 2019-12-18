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
struct nf_conntrack_nat_helper {int /*<<< orphan*/  module; } ;
struct nf_conntrack_helper {int /*<<< orphan*/  nat_mod_name; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct nf_conntrack_nat_helper* nf_conntrack_nat_helper_find (int /*<<< orphan*/ ) ; 

void nf_nat_helper_put(struct nf_conntrack_helper *helper)
{
	struct nf_conntrack_nat_helper *nat;

	nat = nf_conntrack_nat_helper_find(helper->nat_mod_name);
	if (WARN_ON_ONCE(!nat))
		return;

	module_put(nat->module);
}