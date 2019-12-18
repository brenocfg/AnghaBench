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
struct Range6List {unsigned int count; int /*<<< orphan*/ * list; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
todo_remove_at(struct Range6List *targets, unsigned index)
{
    memmove(&targets->list[index],
            &targets->list[index+1],
            (targets->count - index) * sizeof(targets->list[index])
            );
    targets->count--;
}