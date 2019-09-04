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
struct trace_seq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char const*,unsigned char,unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static void print_ip4_addr(struct trace_seq *s, char i, unsigned char *buf)
{
	const char *fmt;

	if (i == 'i')
		fmt = "%03d.%03d.%03d.%03d";
	else
		fmt = "%d.%d.%d.%d";

	trace_seq_printf(s, fmt, buf[0], buf[1], buf[2], buf[3]);
}