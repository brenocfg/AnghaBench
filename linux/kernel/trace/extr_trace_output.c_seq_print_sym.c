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
 int /*<<< orphan*/  kallsyms_lookup (unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 char* kretprobed (char*) ; 
 int /*<<< orphan*/  sprint_symbol (char*,unsigned long) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,unsigned long) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char const*) ; 

__attribute__((used)) static void
seq_print_sym(struct trace_seq *s, unsigned long address, bool offset)
{
#ifdef CONFIG_KALLSYMS
	char str[KSYM_SYMBOL_LEN];
	const char *name;

	if (offset)
		sprint_symbol(str, address);
	else
		kallsyms_lookup(address, NULL, NULL, NULL, str);
	name = kretprobed(str);

	if (name && strlen(name)) {
		trace_seq_puts(s, name);
		return;
	}
#endif
	trace_seq_printf(s, "0x%08lx", address);
}