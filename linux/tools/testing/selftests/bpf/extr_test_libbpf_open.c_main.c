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
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int EXIT_FAIL_OPTION ; 
 int debug ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  libbpf_debug_print ; 
 int /*<<< orphan*/  libbpf_set_print (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  long_options ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int test_open_file (char*,int) ; 
 int /*<<< orphan*/  usage (char**) ; 

int main(int argc, char **argv)
{
	char filename[1024] = { 0 };
	bool verbose = 1;
	int longindex = 0;
	int opt;

	libbpf_set_print(libbpf_debug_print);

	/* Parse commands line args */
	while ((opt = getopt_long(argc, argv, "hDq",
				  long_options, &longindex)) != -1) {
		switch (opt) {
		case 'D':
			debug = 1;
			break;
		case 'q': /* Use in scripting mode */
			verbose = 0;
			break;
		case 'h':
		default:
			usage(argv);
			return EXIT_FAIL_OPTION;
		}
	}
	if (optind >= argc) {
		usage(argv);
		printf("ERROR: Expected BPF_FILE argument after options\n");
		return EXIT_FAIL_OPTION;
	}
	snprintf(filename, sizeof(filename), "%s", argv[optind]);

	return test_open_file(filename, verbose);
}