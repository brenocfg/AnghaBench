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
struct dependency_info {struct dependency_info* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (struct dependency_info*) ; 

__attribute__((used)) static void dependency_entry_free(struct dependency_info *dependency)
{
    heap_free(dependency->id);
    heap_free(dependency);
}