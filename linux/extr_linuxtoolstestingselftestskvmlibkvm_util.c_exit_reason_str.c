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
struct TYPE_3__ {unsigned int reason; char const* name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* exit_reasons_known ; 

const char *exit_reason_str(unsigned int exit_reason)
{
	unsigned int n1;

	for (n1 = 0; n1 < ARRAY_SIZE(exit_reasons_known); n1++) {
		if (exit_reason == exit_reasons_known[n1].reason)
			return exit_reasons_known[n1].name;
	}

	return "Unknown";
}