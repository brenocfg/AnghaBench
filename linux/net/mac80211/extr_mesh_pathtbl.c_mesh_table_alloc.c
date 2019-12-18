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
struct mesh_table {int /*<<< orphan*/  walk_lock; int /*<<< orphan*/  gates_lock; int /*<<< orphan*/  entries; int /*<<< orphan*/  walk_head; int /*<<< orphan*/  known_gates; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mesh_table* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mesh_table *mesh_table_alloc(void)
{
	struct mesh_table *newtbl;

	newtbl = kmalloc(sizeof(struct mesh_table), GFP_ATOMIC);
	if (!newtbl)
		return NULL;

	INIT_HLIST_HEAD(&newtbl->known_gates);
	INIT_HLIST_HEAD(&newtbl->walk_head);
	atomic_set(&newtbl->entries,  0);
	spin_lock_init(&newtbl->gates_lock);
	spin_lock_init(&newtbl->walk_lock);

	return newtbl;
}