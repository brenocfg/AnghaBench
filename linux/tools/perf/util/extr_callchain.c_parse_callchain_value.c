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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCVAL_COUNT ; 
 int /*<<< orphan*/  CCVAL_PERCENT ; 
 int /*<<< orphan*/  CCVAL_PERIOD ; 
 TYPE_1__ callchain_param ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_callchain_value(const char *value)
{
	if (!strncmp(value, "percent", strlen(value))) {
		callchain_param.value = CCVAL_PERCENT;
		return 0;
	}
	if (!strncmp(value, "period", strlen(value))) {
		callchain_param.value = CCVAL_PERIOD;
		return 0;
	}
	if (!strncmp(value, "count", strlen(value))) {
		callchain_param.value = CCVAL_COUNT;
		return 0;
	}
	return -1;
}