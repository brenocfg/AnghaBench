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
 void* atoi (int /*<<< orphan*/ ) ; 
 void* clos_desired ; 
 void* clos_epp ; 
 void* clos_max ; 
 void* clos_min ; 
 void* clos_priority_type ; 
 void* clos_prop_prio ; 
 int cmd_help ; 
 void* current_clos ; 
 int /*<<< orphan*/  exit (int) ; 
 int fact_avx ; 
 void* fact_bucket ; 
 int /*<<< orphan*/  fact_trl ; 
 int force_online_offline ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getopt_long (int,char**,char*,struct option*,int*) ; 
#define  no_argument 129 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  printf (char*) ; 
#define  required_argument 128 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 void* tdp_level ; 

__attribute__((used)) static void parse_cmd_args(int argc, int start, char **argv)
{
	int opt;
	int option_index;

	static struct option long_options[] = {
		{ "bucket", required_argument, 0, 'b' },
		{ "level", required_argument, 0, 'l' },
		{ "online", required_argument, 0, 'o' },
		{ "trl-type", required_argument, 0, 'r' },
		{ "trl", required_argument, 0, 't' },
		{ "help", no_argument, 0, 'h' },
		{ "clos", required_argument, 0, 'c' },
		{ "desired", required_argument, 0, 'd' },
		{ "epp", required_argument, 0, 'e' },
		{ "min", required_argument, 0, 'n' },
		{ "max", required_argument, 0, 'm' },
		{ "priority", required_argument, 0, 'p' },
		{ "weight", required_argument, 0, 'w' },
		{ 0, 0, 0, 0 }
	};

	option_index = start;

	optind = start + 1;
	while ((opt = getopt_long(argc, argv, "b:l:t:c:d:e:n:m:p:w:ho",
				  long_options, &option_index)) != -1) {
		switch (opt) {
		case 'b':
			fact_bucket = atoi(optarg);
			break;
		case 'h':
			cmd_help = 1;
			break;
		case 'l':
			tdp_level = atoi(optarg);
			break;
		case 'o':
			force_online_offline = 1;
			break;
		case 't':
			sscanf(optarg, "0x%llx", &fact_trl);
			break;
		case 'r':
			if (!strncmp(optarg, "sse", 3)) {
				fact_avx = 0x01;
			} else if (!strncmp(optarg, "avx2", 4)) {
				fact_avx = 0x02;
			} else if (!strncmp(optarg, "avx512", 4)) {
				fact_avx = 0x04;
			} else {
				fprintf(outf, "Invalid sse,avx options\n");
				exit(1);
			}
			break;
		/* CLOS related */
		case 'c':
			current_clos = atoi(optarg);
			break;
		case 'd':
			clos_desired = atoi(optarg);
			break;
		case 'e':
			clos_epp = atoi(optarg);
			break;
		case 'n':
			clos_min = atoi(optarg);
			break;
		case 'm':
			clos_max = atoi(optarg);
			break;
		case 'p':
			clos_priority_type = atoi(optarg);
			break;
		case 'w':
			clos_prop_prio = atoi(optarg);
			break;
		default:
			printf("no match\n");
		}
	}
}