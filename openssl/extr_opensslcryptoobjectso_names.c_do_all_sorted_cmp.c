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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ OBJ_NAME ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_all_sorted_cmp(const void *n1_, const void *n2_)
{
    const OBJ_NAME *const *n1 = n1_;
    const OBJ_NAME *const *n2 = n2_;

    return strcmp((*n1)->name, (*n2)->name);
}