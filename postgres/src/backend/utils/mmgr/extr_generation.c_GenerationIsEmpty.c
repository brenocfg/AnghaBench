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
struct TYPE_2__ {int /*<<< orphan*/  blocks; } ;
typedef  scalar_t__ MemoryContext ;
typedef  TYPE_1__ GenerationContext ;

/* Variables and functions */
 int dlist_is_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
GenerationIsEmpty(MemoryContext context)
{
	GenerationContext *set = (GenerationContext *) context;

	return dlist_is_empty(&set->blocks);
}