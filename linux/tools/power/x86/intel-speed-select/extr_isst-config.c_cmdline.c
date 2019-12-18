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
struct option {char* member_0; char member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  const member_1; } ;

/* Variables and functions */
 int cpu_model ; 
 int debug_flag ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen_or_exit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_cpu_set (int /*<<< orphan*/ ) ; 
 scalar_t__ geteuid () ; 
 int getopt_long_only (int,char**,char*,struct option*,int*) ; 
 int isst_fill_platform_info () ; 
 int /*<<< orphan*/  isst_print_platform_information () ; 
#define  no_argument 129 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int out_format_json ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  parse_cpu_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  present_cpumask ; 
 int /*<<< orphan*/  print_version () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  process_command (int,char**) ; 
 char* progname ; 
#define  required_argument 128 
 int /*<<< orphan*/  set_cpu_present_cpu_mask () ; 
 int /*<<< orphan*/  set_cpu_target_cpu_mask () ; 
 int /*<<< orphan*/  set_max_cpu_num () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  target_cpumask ; 
 int /*<<< orphan*/  update_cpu_model () ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static void cmdline(int argc, char **argv)
{
	int opt;
	int option_index = 0;
	int ret;

	static struct option long_options[] = {
		{ "cpu", required_argument, 0, 'c' },
		{ "debug", no_argument, 0, 'd' },
		{ "format", required_argument, 0, 'f' },
		{ "help", no_argument, 0, 'h' },
		{ "info", no_argument, 0, 'i' },
		{ "out", required_argument, 0, 'o' },
		{ "version", no_argument, 0, 'v' },
		{ 0, 0, 0, 0 }
	};

	progname = argv[0];
	while ((opt = getopt_long_only(argc, argv, "+c:df:hio:v", long_options,
				       &option_index)) != -1) {
		switch (opt) {
		case 'c':
			parse_cpu_command(optarg);
			break;
		case 'd':
			debug_flag = 1;
			printf("Debug Mode ON\n");
			break;
		case 'f':
			if (!strncmp(optarg, "json", 4))
				out_format_json = 1;
			break;
		case 'h':
			usage();
			break;
		case 'i':
			isst_print_platform_information();
			break;
		case 'o':
			if (outf)
				fclose(outf);
			outf = fopen_or_exit(optarg, "w");
			break;
		case 'v':
			print_version();
			break;
		default:
			usage();
		}
	}

	if (geteuid() != 0) {
		fprintf(stderr, "Must run as root\n");
		exit(0);
	}

	if (optind > (argc - 2)) {
		fprintf(stderr, "Feature name and|or command not specified\n");
		exit(0);
	}
	update_cpu_model();
	printf("Intel(R) Speed Select Technology\n");
	printf("Executing on CPU model:%d[0x%x]\n", cpu_model, cpu_model);
	set_max_cpu_num();
	set_cpu_present_cpu_mask();
	set_cpu_target_cpu_mask();
	ret = isst_fill_platform_info();
	if (ret)
		goto out;

	process_command(argc, argv);
out:
	free_cpu_set(present_cpumask);
	free_cpu_set(target_cpumask);
}