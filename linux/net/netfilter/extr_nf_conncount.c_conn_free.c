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
struct nf_conncount_tuple {int /*<<< orphan*/  node; } ;
struct nf_conncount_list {int /*<<< orphan*/  count; int /*<<< orphan*/  list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  conncount_conn_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nf_conncount_tuple*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void conn_free(struct nf_conncount_list *list,
		      struct nf_conncount_tuple *conn)
{
	lockdep_assert_held(&list->list_lock);

	list->count--;
	list_del(&conn->node);

	kmem_cache_free(conncount_conn_cachep, conn);
}