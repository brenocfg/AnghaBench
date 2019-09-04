#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  linebuf ;
typedef  enum idlestate_value { ____Placeholder_idlestate_value } idlestate_value ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int MAX_IDLESTATE_VALUE_FILES ; 
 int MAX_LINE_LEN ; 
 unsigned int cpuidle_state_read_file (unsigned int,unsigned int,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * idlestate_value_files ; 
 unsigned long long strtoull (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
unsigned long long cpuidle_state_get_one_value(unsigned int cpu,
					       unsigned int idlestate,
					       enum idlestate_value which)
{
	unsigned long long value;
	unsigned int len;
	char linebuf[MAX_LINE_LEN];
	char *endp;

	if (which >= MAX_IDLESTATE_VALUE_FILES)
		return 0;

	len = cpuidle_state_read_file(cpu, idlestate,
				      idlestate_value_files[which],
				      linebuf, sizeof(linebuf));
	if (len == 0)
		return 0;

	value = strtoull(linebuf, &endp, 0);

	if (endp == linebuf || errno == ERANGE)
		return 0;

	return value;
}