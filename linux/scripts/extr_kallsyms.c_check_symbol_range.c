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
struct addr_range {unsigned long long start; unsigned long long end; int /*<<< orphan*/  end_sym; int /*<<< orphan*/  start_sym; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_symbol_range(const char *sym, unsigned long long addr,
			      struct addr_range *ranges, int entries)
{
	size_t i;
	struct addr_range *ar;

	for (i = 0; i < entries; ++i) {
		ar = &ranges[i];

		if (strcmp(sym, ar->start_sym) == 0) {
			ar->start = addr;
			return 0;
		} else if (strcmp(sym, ar->end_sym) == 0) {
			ar->end = addr;
			return 0;
		}
	}

	return 1;
}