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
 int KSYM_SYMBOL_LEN ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char const*,char*) ; 

__attribute__((used)) static void
seq_print_sym_short(struct trace_seq *s, const char *fmt, unsigned long address)
{
	char str[KSYM_SYMBOL_LEN];
#ifdef CONFIG_KALLSYMS
	const char *name;

	kallsyms_lookup(address, NULL, NULL, NULL, str);

	name = kretprobed(str);

	if (name && strlen(name)) {
		trace_seq_printf(s, fmt, name);
		return;
	}
#endif
	snprintf(str, KSYM_SYMBOL_LEN, "0x%08lx", address);
	trace_seq_printf(s, fmt, str);
}