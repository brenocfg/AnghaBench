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
struct TYPE_2__ {long addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int sym_cnt ; 
 TYPE_1__* syms ; 

long ksym_get_addr(const char *name)
{
	int i;

	for (i = 0; i < sym_cnt; i++) {
		if (strcmp(syms[i].name, name) == 0)
			return syms[i].addr;
	}

	return 0;
}