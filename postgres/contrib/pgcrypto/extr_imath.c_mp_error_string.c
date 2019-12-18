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
typedef  int mp_result ;

/* Variables and functions */
 char const** s_error_msg ; 
 char const* s_unknown_err ; 

const char *
mp_error_string(mp_result res)
{
	if (res > 0)
		return s_unknown_err;

	res = -res;
	int			ix;

	for (ix = 0; ix < res && s_error_msg[ix] != NULL; ++ix)
		;

	if (s_error_msg[ix] != NULL)
	{
		return s_error_msg[ix];
	}
	else
	{
		return s_unknown_err;
	}
}