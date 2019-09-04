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
struct nf_conntrack_helper {int /*<<< orphan*/  hnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  expect_iter_me ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_expect_iterate_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_helper_count ; 
 int /*<<< orphan*/  nf_ct_helper_mutex ; 
 int /*<<< orphan*/  nf_ct_iterate_destroy (int /*<<< orphan*/ ,struct nf_conntrack_helper*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  unhelp ; 

void nf_conntrack_helper_unregister(struct nf_conntrack_helper *me)
{
	mutex_lock(&nf_ct_helper_mutex);
	hlist_del_rcu(&me->hnode);
	nf_ct_helper_count--;
	mutex_unlock(&nf_ct_helper_mutex);

	/* Make sure every nothing is still using the helper unless its a
	 * connection in the hash.
	 */
	synchronize_rcu();

	nf_ct_expect_iterate_destroy(expect_iter_me, NULL);
	nf_ct_iterate_destroy(unhelp, me);

	/* Maybe someone has gotten the helper already when unhelp above.
	 * So need to wait it.
	 */
	synchronize_rcu();
}