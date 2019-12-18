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
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int maccalc_do_add (int,char const**) ; 
 int maccalc_do_and (int,char const**) ; 
 int maccalc_do_bin2mac (int,char const**) ; 
 int maccalc_do_mac2bin (int,char const**) ; 
 int maccalc_do_or (int,char const**) ; 
 int maccalc_do_xor (int,char const**) ; 
 char* maccalc_name ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, const char *argv[])
{
	int (*op)(int argc, const char *argv[]);
	int ret;

	maccalc_name = (char *) argv[0];

	if (argc < 2) {
		usage();
		return EXIT_FAILURE;
	}

	if (strcmp(argv[1], "add") == 0) {
		op = maccalc_do_add;
	} else if (strcmp(argv[1], "and") == 0) {
		op = maccalc_do_and;
	} else if (strcmp(argv[1], "or") == 0) {
		op = maccalc_do_or;
	} else if (strcmp(argv[1], "xor") == 0) {
		op = maccalc_do_xor;
	} else if (strcmp(argv[1], "mac2bin") == 0) {
		op = maccalc_do_mac2bin;
	} else if (strcmp(argv[1], "bin2mac") == 0) {
		op = maccalc_do_bin2mac;
	} else {
		fprintf(stderr, "unknown command '%s'\n", argv[1]);
		usage();
		return EXIT_FAILURE;
	}

	argc -= 2;
	argv += 2;

	ret = op(argc, argv);
	if (ret)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}