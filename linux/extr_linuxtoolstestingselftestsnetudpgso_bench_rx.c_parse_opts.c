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
 int /*<<< orphan*/  cfg_port ; 
 int cfg_tcp ; 
 int cfg_verify ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 

__attribute__((used)) static void parse_opts(int argc, char **argv)
{
	int c;

	while ((c = getopt(argc, argv, "ptv")) != -1) {
		switch (c) {
		case 'p':
			cfg_port = htons(strtoul(optarg, NULL, 0));
			break;
		case 't':
			cfg_tcp = true;
			break;
		case 'v':
			cfg_verify = true;
			break;
		}
	}

	if (optind != argc)
		usage(argv[0]);

	if (cfg_tcp && cfg_verify)
		error(1, 0, "TODO: implement verify mode for tcp");
}