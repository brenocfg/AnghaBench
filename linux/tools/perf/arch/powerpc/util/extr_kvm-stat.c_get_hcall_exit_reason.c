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
typedef  scalar_t__ u64 ;
struct exit_reasons_table {char const* reason; scalar_t__ exit_code; } ;

/* Variables and functions */
 struct exit_reasons_table* hcall_reasons ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long) ; 

__attribute__((used)) static const char *get_hcall_exit_reason(u64 exit_code)
{
	struct exit_reasons_table *tbl = hcall_reasons;

	while (tbl->reason != NULL) {
		if (tbl->exit_code == exit_code)
			return tbl->reason;
		tbl++;
	}

	pr_debug("Unknown hcall code: %lld\n",
	       (unsigned long long)exit_code);
	return "UNKNOWN";
}