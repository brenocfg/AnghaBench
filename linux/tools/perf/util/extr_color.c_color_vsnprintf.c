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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int __color_vsnprintf (char*,size_t,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int color_vsnprintf(char *bf, size_t size, const char *color,
		    const char *fmt, va_list args)
{
	return __color_vsnprintf(bf, size, color, fmt, args, NULL);
}