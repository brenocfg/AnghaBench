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
struct TYPE_2__ {int branch_callstack; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCKEY_ADDRESS ; 
 int /*<<< orphan*/  CCKEY_FUNCTION ; 
 int /*<<< orphan*/  CCKEY_SRCLINE ; 
 TYPE_1__ callchain_param ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_callchain_sort_key(const char *value)
{
	if (!strncmp(value, "function", strlen(value))) {
		callchain_param.key = CCKEY_FUNCTION;
		return 0;
	}
	if (!strncmp(value, "address", strlen(value))) {
		callchain_param.key = CCKEY_ADDRESS;
		return 0;
	}
	if (!strncmp(value, "srcline", strlen(value))) {
		callchain_param.key = CCKEY_SRCLINE;
		return 0;
	}
	if (!strncmp(value, "branch", strlen(value))) {
		callchain_param.branch_callstack = 1;
		return 0;
	}
	return -1;
}