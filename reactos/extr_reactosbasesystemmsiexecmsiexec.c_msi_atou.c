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
typedef  char* LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */

__attribute__((used)) static DWORD msi_atou(LPCWSTR str)
{
	DWORD ret = 0;
	while(*str >= '0' && *str <= '9')
	{
		ret *= 10;
		ret += (*str - '0');
		str++;
	}
	return ret;
}