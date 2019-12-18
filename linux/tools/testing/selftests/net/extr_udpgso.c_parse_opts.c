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
 int cfg_do_connected ; 
 int cfg_do_connectionless ; 
 int cfg_do_ipv4 ; 
 int cfg_do_ipv6 ; 
 int cfg_do_msgmore ; 
 int cfg_do_setsockopt ; 
 int /*<<< orphan*/  cfg_specific_test_id ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_opts(int argc, char **argv)
{
	int c;

	while ((c = getopt(argc, argv, "46cCmst:")) != -1) {
		switch (c) {
		case '4':
			cfg_do_ipv4 = true;
			break;
		case '6':
			cfg_do_ipv6 = true;
			break;
		case 'c':
			cfg_do_connected = true;
			break;
		case 'C':
			cfg_do_connectionless = true;
			break;
		case 'm':
			cfg_do_msgmore = true;
			break;
		case 's':
			cfg_do_setsockopt = true;
			break;
		case 't':
			cfg_specific_test_id = strtoul(optarg, NULL, 0);
			break;
		default:
			error(1, 0, "%s: parse error", argv[0]);
		}
	}
}