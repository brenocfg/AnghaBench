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
struct xt_set_info {int /*<<< orphan*/  index; } ;
struct tcf_ematch {scalar_t__ data; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_set_nfnl_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static void em_ipset_destroy(struct tcf_ematch *em)
{
	const struct xt_set_info *set = (const void *) em->data;
	if (set) {
		ip_set_nfnl_put(em->net, set->index);
		kfree((void *) em->data);
	}
}