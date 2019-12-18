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
 int /*<<< orphan*/  cfg_label ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_opts(int argc, char **argv)
{
	int c;

	while ((c = getopt(argc, argv, "l:")) != -1) {
		switch (c) {
		case 'l':
			cfg_label = strtoul(optarg, NULL, 0);
			break;
		default:
			error(1, 0, "%s: parse error", argv[0]);
		}
	}
}