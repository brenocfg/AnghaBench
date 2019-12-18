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
struct configfs_fragment {int frag_dead; int /*<<< orphan*/  frag_sem; int /*<<< orphan*/  frag_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 struct configfs_fragment* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct configfs_fragment *new_fragment(void)
{
	struct configfs_fragment *p;

	p = kmalloc(sizeof(struct configfs_fragment), GFP_KERNEL);
	if (p) {
		atomic_set(&p->frag_count, 1);
		init_rwsem(&p->frag_sem);
		p->frag_dead = false;
	}
	return p;
}