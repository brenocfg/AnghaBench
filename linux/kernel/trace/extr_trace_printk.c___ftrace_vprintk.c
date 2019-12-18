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
 int /*<<< orphan*/  trace_printk_enabled ; 
 int trace_vprintk (unsigned long,char const*,int /*<<< orphan*/ ) ; 

int __ftrace_vprintk(unsigned long ip, const char *fmt, va_list ap)
{
	if (!trace_printk_enabled)
		return 0;

	return trace_vprintk(ip, fmt, ap);
}