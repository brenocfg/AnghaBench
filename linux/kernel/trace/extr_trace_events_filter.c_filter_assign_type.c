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
 int FILTER_DYN_STRING ; 
 int FILTER_OTHER ; 
 int FILTER_PTR_STRING ; 
 int FILTER_STATIC_STRING ; 
 scalar_t__ strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strstr (char const*,char*) ; 

int filter_assign_type(const char *type)
{
	if (strstr(type, "__data_loc") && strstr(type, "char"))
		return FILTER_DYN_STRING;

	if (strchr(type, '[') && strstr(type, "char"))
		return FILTER_STATIC_STRING;

	if (strcmp(type, "char *") == 0 || strcmp(type, "const char *") == 0)
		return FILTER_PTR_STRING;

	return FILTER_OTHER;
}