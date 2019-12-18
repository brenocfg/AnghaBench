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
struct recorded_ref {int /*<<< orphan*/  list; int /*<<< orphan*/ * full_path; int /*<<< orphan*/  dir_gen; int /*<<< orphan*/  dir; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct recorded_ref* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static int dup_ref(struct recorded_ref *ref, struct list_head *list)
{
	struct recorded_ref *new;

	new = kmalloc(sizeof(*ref), GFP_KERNEL);
	if (!new)
		return -ENOMEM;

	new->dir = ref->dir;
	new->dir_gen = ref->dir_gen;
	new->full_path = NULL;
	INIT_LIST_HEAD(&new->list);
	list_add_tail(&new->list, list);
	return 0;
}