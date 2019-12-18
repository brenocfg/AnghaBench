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
typedef  int int16 ;

/* Variables and functions */
 int pg_mblen (char*) ; 
 int /*<<< orphan*/  t_iseq (char*,char) ; 

__attribute__((used)) static char *
get_modifiers(char *buf, int16 *weight, bool *prefix)
{
	*weight = 0;
	*prefix = false;

	if (!t_iseq(buf, ':'))
		return buf;

	buf++;
	while (*buf && pg_mblen(buf) == 1)
	{
		switch (*buf)
		{
			case 'a':
			case 'A':
				*weight |= 1 << 3;
				break;
			case 'b':
			case 'B':
				*weight |= 1 << 2;
				break;
			case 'c':
			case 'C':
				*weight |= 1 << 1;
				break;
			case 'd':
			case 'D':
				*weight |= 1;
				break;
			case '*':
				*prefix = true;
				break;
			default:
				return buf;
		}
		buf++;
	}

	return buf;
}