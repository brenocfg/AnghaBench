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
 int r_str_ansi_nlen (char const*,int) ; 
 char tolower (char const) ; 

__attribute__((used)) static bool is_indirect_reg(char const*str)
{
	if ( !str) {
		return false;
	}

	if (str[0] == '@' ) {
		return r_str_ansi_nlen (str, 4) == 3
			&& tolower (str[1]) == 'r'
			&& (str[2] == '0' || str[2] == '1');
	}

	if (str[0] == '[' ) {
		return r_str_ansi_nlen (str, 5) == 4
			&& tolower (str[1]) == 'r'
			&& (str[2] == '0' || str[2] == '1')
			&& str[3] == ']';
	}

	return false;
}