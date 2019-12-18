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
 char* bstrdup_n (char const*,int) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static bool getparam(const char *param, char **name, const char **value)
{
	const char *assign;

	if (!param || !*param || (*param == '='))
		return false;

	assign = strchr(param, '=');
	if (!assign || !*assign || !*(assign + 1))
		return false;

	*name = bstrdup_n(param, assign - param);
	*value = assign + 1;
	return true;
}