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
struct byt_pingroup {int nfuncs; TYPE_1__* mixed_funcs; } ;
struct TYPE_2__ {unsigned short* func_values; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int byt_get_group_mixed_mux(const struct byt_pingroup group,
				   const char *func_name,
				   const unsigned short **func)
{
	int i;

	for (i = 0; i < group.nfuncs; i++) {
		if (!strcmp(group.mixed_funcs[i].name, func_name)) {
			*func = group.mixed_funcs[i].func_values;
			return 0;
		}
	}

	return 1;
}