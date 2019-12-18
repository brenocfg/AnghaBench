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

/* Variables and functions */
 int absolute_percpu ; 
 int all_symbols ; 
 int base_relative ; 
 int /*<<< orphan*/  make_percpus_absolute () ; 
 int /*<<< orphan*/  optimize_token_table () ; 
 int /*<<< orphan*/  read_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_relative_base () ; 
 int /*<<< orphan*/  sort_symbols () ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  write_src () ; 

int main(int argc, char **argv)
{
	if (argc >= 2) {
		int i;
		for (i = 1; i < argc; i++) {
			if(strcmp(argv[i], "--all-symbols") == 0)
				all_symbols = 1;
			else if (strcmp(argv[i], "--absolute-percpu") == 0)
				absolute_percpu = 1;
			else if (strcmp(argv[i], "--base-relative") == 0)
				base_relative = 1;
			else
				usage();
		}
	} else if (argc != 1)
		usage();

	read_map(stdin);
	if (absolute_percpu)
		make_percpus_absolute();
	if (base_relative)
		record_relative_base();
	sort_symbols();
	optimize_token_table();
	write_src();

	return 0;
}