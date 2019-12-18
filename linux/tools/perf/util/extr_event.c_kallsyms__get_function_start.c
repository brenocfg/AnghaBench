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
typedef  int /*<<< orphan*/  u64 ;
struct process_symbol_args {char const* name; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_symbol_cb ; 
 scalar_t__ kallsyms__parse (char const*,struct process_symbol_args*,int /*<<< orphan*/ ) ; 

int kallsyms__get_function_start(const char *kallsyms_filename,
				 const char *symbol_name, u64 *addr)
{
	struct process_symbol_args args = { .name = symbol_name, };

	if (kallsyms__parse(kallsyms_filename, &args, find_symbol_cb) <= 0)
		return -1;

	*addr = args.start;
	return 0;
}