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
struct TYPE_2__ {int /*<<< orphan*/  element; } ;

/* Variables and functions */
 scalar_t__ debug_opt ; 
 int /*<<< orphan*/  dump_element (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* type_list ; 

__attribute__((used)) static void dump_elements(void)
{
	if (debug_opt)
		dump_element(type_list[0].element, 0);
}