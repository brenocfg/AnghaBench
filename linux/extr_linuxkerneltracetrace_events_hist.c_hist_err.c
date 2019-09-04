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
 int MAX_FILTER_STR_VAL ; 
 char* hist_err_str ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void hist_err(char *str, char *var)
{
	int maxlen = MAX_FILTER_STR_VAL - 1;

	if (!str)
		return;

	if (strlen(hist_err_str))
		return;

	if (!var)
		var = "";

	if (strlen(hist_err_str) + strlen(str) + strlen(var) > maxlen)
		return;

	strcat(hist_err_str, str);
	strcat(hist_err_str, var);
}