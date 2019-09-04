#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;
struct trace_array {TYPE_1__ trace_buffer; } ;

/* Variables and functions */
 int __trace_array_vprintk (int /*<<< orphan*/ ,unsigned long,char const*,int /*<<< orphan*/ ) ; 

int trace_array_vprintk(struct trace_array *tr,
			unsigned long ip, const char *fmt, va_list args)
{
	return __trace_array_vprintk(tr->trace_buffer.buffer, ip, fmt, args);
}