#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct TYPE_2__* next; } ;
struct pernet_operations {TYPE_1__ list; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 TYPE_1__* first_device ; 
 int /*<<< orphan*/  pernet_ops_rwsem ; 
 int /*<<< orphan*/  unregister_pernet_operations (struct pernet_operations*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void unregister_pernet_device(struct pernet_operations *ops)
{
	down_write(&pernet_ops_rwsem);
	if (&ops->list == first_device)
		first_device = first_device->next;
	unregister_pernet_operations(ops);
	up_write(&pernet_ops_rwsem);
}