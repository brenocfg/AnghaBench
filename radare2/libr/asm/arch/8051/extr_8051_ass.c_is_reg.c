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

__attribute__((used)) static bool is_reg(char const*str)
{
	return str && tolower (str[0]) == 'r' && r_str_ansi_nlen (str, 3) == 2
		&& '0' <= str[1] && str[1] <= '7';
}