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
 int cfg_long_running ; 
 int cfg_verbose ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int,char**,char*) ; 

__attribute__((used)) static void parse_opts(int argc, char **argv)
{
	int c;

	while ((c = getopt(argc, argv, "lv")) != -1) {
		switch (c) {
		case 'l':
			cfg_long_running = true;
			break;
		case 'v':
			cfg_verbose = true;
			break;
		default:
			error(1, 0, "%s: parse error", argv[0]);
		}
	}
}