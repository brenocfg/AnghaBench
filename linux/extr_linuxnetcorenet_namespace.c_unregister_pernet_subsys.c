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
struct pernet_operations {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pernet_ops_rwsem ; 
 int /*<<< orphan*/  unregister_pernet_operations (struct pernet_operations*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void unregister_pernet_subsys(struct pernet_operations *ops)
{
	down_write(&pernet_ops_rwsem);
	unregister_pernet_operations(ops);
	up_write(&pernet_ops_rwsem);
}