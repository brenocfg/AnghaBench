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
struct TYPE_2__ {int last_access; int /*<<< orphan*/ * clk_tw1; int /*<<< orphan*/ * clk_tw0; int /*<<< orphan*/  clk_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  _set_timing (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ sossi ; 

__attribute__((used)) static inline void set_timing(int access)
{
	if (access != sossi.last_access) {
		sossi.last_access = access;
		_set_timing(sossi.clk_div,
			    sossi.clk_tw0[access], sossi.clk_tw1[access]);
	}
}