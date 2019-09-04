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
 char php_last_char ; 

__attribute__((used)) static size_t readline_shell_ub_write(const char *str, size_t str_length) /* {{{ */
{
	/* We just store the last char here and then pass back to the
	   caller (sapi_cli_single_write in sapi/cli) which will actually
	   write due to -1 return code */
	php_last_char = str[str_length-1];

	return (size_t) -1;
}