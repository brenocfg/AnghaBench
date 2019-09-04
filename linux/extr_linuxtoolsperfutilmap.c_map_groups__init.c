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
struct map_groups {int /*<<< orphan*/  refcnt; struct machine* machine; int /*<<< orphan*/  maps; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  maps__init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

void map_groups__init(struct map_groups *mg, struct machine *machine)
{
	maps__init(&mg->maps);
	mg->machine = machine;
	refcount_set(&mg->refcnt, 1);
}