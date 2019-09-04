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
typedef  char u32 ;

/* Variables and functions */

u32 MapCharToHexDigit(char chTmp)
{
	if (chTmp >= '0' && chTmp <= '9')
		return (chTmp - '0');
	else if (chTmp >= 'a' && chTmp <= 'f')
		return (10 + (chTmp - 'a'));
	else if (chTmp >= 'A' && chTmp <= 'F')
		return (10 + (chTmp - 'A'));
	else
		return 0;
}