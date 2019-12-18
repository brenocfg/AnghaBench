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
struct list {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_insert (int /*<<< orphan*/ ,struct list*) ; 

__attribute__((used)) static inline void
list_prepend(struct list *list, struct list *new_link)
{
	list_insert(list->next, new_link);
}