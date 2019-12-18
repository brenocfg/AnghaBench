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
struct argv {size_t const argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  adjust_power_of_2 (size_t const) ; 
 int /*<<< orphan*/  argv_extend (struct argv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
argv_grow(struct argv *a, const size_t add)
{
    const size_t newargc = a->argc + add + 1;
    ASSERT(newargc > a->argc);
    argv_extend(a, adjust_power_of_2(newargc));
}