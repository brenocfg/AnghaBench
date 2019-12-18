#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  replace; } ;

/* Variables and functions */
 int klp_enable_patch (TYPE_1__*) ; 
 TYPE_1__ patch ; 
 int /*<<< orphan*/  replace ; 

__attribute__((used)) static int test_klp_callbacks_demo2_init(void)
{
	patch.replace = replace;
	return klp_enable_patch(&patch);
}