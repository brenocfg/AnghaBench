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
struct option {char* member_0; int member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  Usage () ; 
 double atoi (int /*<<< orphan*/ ) ; 
 int debugFlag ; 
 double dur ; 
 int edt_flag ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char) ; 
 int getopt_long (int,char**,char*,struct option*,int /*<<< orphan*/ *) ; 
 int loopback_flag ; 
 double minRate ; 
 int no_cn_flag ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 char optopt ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 double rate ; 
 int run_bpf_prog (char*,int) ; 
 int stats_flag ; 
 int /*<<< orphan*/  stderr ; 
 int work_conserving_flag ; 

int main(int argc, char **argv)
{
	char *prog = "hbm_out_kern.o";
	int  k;
	int cg_id = 1;
	char *optstring = "iodln:r:st:wh";
	struct option loptions[] = {
		{"no_cn", 0, NULL, 1},
		{"edt", 0, NULL, 2},
		{NULL, 0, NULL, 0}
	};

	while ((k = getopt_long(argc, argv, optstring, loptions, NULL)) != -1) {
		switch (k) {
		case 1:
			no_cn_flag = true;
			break;
		case 2:
			prog = "hbm_edt_kern.o";
			edt_flag = true;
			break;
		case'o':
			break;
		case 'd':
			debugFlag = true;
			break;
		case 'l':
			loopback_flag = true;
			break;
		case 'n':
			cg_id = atoi(optarg);
			break;
		case 'r':
			minRate = atoi(optarg) * 1.024;
			rate = minRate;
			break;
		case 's':
			stats_flag = true;
			break;
		case 't':
			dur = atoi(optarg);
			break;
		case 'w':
			work_conserving_flag = true;
			break;
		case '?':
			if (optopt == 'n' || optopt == 'r' || optopt == 't')
				fprintf(stderr,
					"Option -%c requires an argument.\n\n",
					optopt);
		case 'h':
			// fallthrough
		default:
			Usage();
			return 0;
		}
	}

	if (optind < argc)
		prog = argv[optind];
	printf("HBM prog: %s\n", prog != NULL ? prog : "NULL");

	return run_bpf_prog(prog, cg_id);
}