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
struct xt_hashlimit_htable {scalar_t__ family; int /*<<< orphan*/  name; int /*<<< orphan*/  net; } ;
struct proc_dir_entry {int dummy; } ;
struct hashlimit_net {struct proc_dir_entry* ip6t_hashlimit; struct proc_dir_entry* ipt_hashlimit; } ;

/* Variables and functions */
 scalar_t__ NFPROTO_IPV4 ; 
 struct hashlimit_net* hashlimit_pernet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,struct proc_dir_entry*) ; 

__attribute__((used)) static void htable_remove_proc_entry(struct xt_hashlimit_htable *hinfo)
{
	struct hashlimit_net *hashlimit_net = hashlimit_pernet(hinfo->net);
	struct proc_dir_entry *parent;

	if (hinfo->family == NFPROTO_IPV4)
		parent = hashlimit_net->ipt_hashlimit;
	else
		parent = hashlimit_net->ip6t_hashlimit;

	if (parent != NULL)
		remove_proc_entry(hinfo->name, parent);
}