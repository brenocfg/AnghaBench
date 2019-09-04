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
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  out_of_memory () ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *json_strdup(const char *str)
{
	char *ret = (char*) malloc(strlen(str) + 1);
	if (ret == NULL)
		out_of_memory();
	strcpy(ret, str);
	return ret;
}