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
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,...) ; 

__attribute__((used)) static void print_ip6_addr(struct trace_seq *s, char i, unsigned char *buf)
{
	int j;

	for (j = 0; j < 16; j += 2) {
		trace_seq_printf(s, "%02x%02x", buf[j], buf[j+1]);
		if (i == 'I' && j < 14)
			trace_seq_printf(s, ":");
	}
}