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
struct btree_head {int /*<<< orphan*/  mempool; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __btree_init (struct btree_head*) ; 
 int /*<<< orphan*/  btree_alloc ; 
 int /*<<< orphan*/  btree_free ; 
 int /*<<< orphan*/  mempool_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btree_init(struct btree_head *head)
{
	__btree_init(head);
	head->mempool = mempool_create(0, btree_alloc, btree_free, NULL);
	if (!head->mempool)
		return -ENOMEM;
	return 0;
}