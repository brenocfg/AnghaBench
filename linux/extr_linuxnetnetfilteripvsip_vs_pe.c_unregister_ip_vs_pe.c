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
struct ip_vs_pe {int /*<<< orphan*/  name; int /*<<< orphan*/  n_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_vs_pe_mutex ; 
 int /*<<< orphan*/  ip_vs_use_count_dec () ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

int unregister_ip_vs_pe(struct ip_vs_pe *pe)
{
	mutex_lock(&ip_vs_pe_mutex);
	/* Remove it from the d-linked pe list */
	list_del_rcu(&pe->n_list);
	mutex_unlock(&ip_vs_pe_mutex);

	/* decrease the module use count */
	ip_vs_use_count_dec();

	pr_info("[%s] pe unregistered.\n", pe->name);

	return 0;
}