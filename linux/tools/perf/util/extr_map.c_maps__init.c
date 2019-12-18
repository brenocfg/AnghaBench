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
struct maps {int /*<<< orphan*/  lock; void* names; void* entries; } ;

/* Variables and functions */
 void* RB_ROOT ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void maps__init(struct maps *maps)
{
	maps->entries = RB_ROOT;
	maps->names = RB_ROOT;
	init_rwsem(&maps->lock);
}