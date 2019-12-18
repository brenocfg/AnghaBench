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
 char TOUPPER (char) ; 
 scalar_t__ xisdigit (char) ; 

__attribute__((used)) static char xchartohex(char c)
{
	if (xisdigit(c))
		return c - '0';

	c = TOUPPER(c);
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;

	return c;
}