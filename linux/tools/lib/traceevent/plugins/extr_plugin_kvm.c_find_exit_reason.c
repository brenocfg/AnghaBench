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
struct str_values {int val; char const* str; } ;
struct TYPE_2__ {unsigned int isa; struct str_values* strings; } ;

/* Variables and functions */
 TYPE_1__* isa_exit_reasons ; 

__attribute__((used)) static const char *find_exit_reason(unsigned isa, int val)
{
	struct str_values *strings = NULL;
	int i;

	for (i = 0; isa_exit_reasons[i].strings; ++i)
		if (isa_exit_reasons[i].isa == isa) {
			strings = isa_exit_reasons[i].strings;
			break;
		}
	if (!strings)
		return "UNKNOWN-ISA";
	for (i = 0; strings[i].val >= 0; i++)
		if (strings[i].val == val)
			break;

	return strings[i].str;
}