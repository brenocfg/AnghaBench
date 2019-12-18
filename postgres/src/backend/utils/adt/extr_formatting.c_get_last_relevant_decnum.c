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

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_elog_output ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static char *
get_last_relevant_decnum(char *num)
{
	char	   *result,
			   *p = strchr(num, '.');

#ifdef DEBUG_TO_FROM_CHAR
	elog(DEBUG_elog_output, "get_last_relevant_decnum()");
#endif

	if (!p)
		return NULL;

	result = p;

	while (*(++p))
	{
		if (*p != '0')
			result = p;
	}

	return result;
}