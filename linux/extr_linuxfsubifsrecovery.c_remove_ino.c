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
struct ubifs_info {int /*<<< orphan*/  size_tree; } ;
struct size_entry {int /*<<< orphan*/  rb; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 struct size_entry* find_ino (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct size_entry*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_ino(struct ubifs_info *c, ino_t inum)
{
	struct size_entry *e = find_ino(c, inum);

	if (!e)
		return;
	rb_erase(&e->rb, &c->size_tree);
	kfree(e);
}