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
struct aa_ns {int /*<<< orphan*/  sub_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  __aa_findn_ns (int /*<<< orphan*/ *,char const*,size_t) ; 
 struct aa_ns* aa_get_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct aa_ns *aa_findn_ns(struct aa_ns *root, const char *name, size_t n)
{
	struct aa_ns *ns = NULL;

	rcu_read_lock();
	ns = aa_get_ns(__aa_findn_ns(&root->sub_ns, name, n));
	rcu_read_unlock();

	return ns;
}