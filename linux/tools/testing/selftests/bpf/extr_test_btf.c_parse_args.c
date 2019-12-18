#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int always_log; int file_test_num; int file_test; int raw_test_num; int raw_test; int get_info_test_num; int get_info_test; int pprint_test; int info_raw_test_num; int info_raw_test; int dedup_test_num; int dedup_test; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 TYPE_1__ args ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dedup_tests ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_tests ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_info_tests ; 
 int getopt (int,char**,char const*) ; 
 int /*<<< orphan*/  info_raw_tests ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  raw_tests ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (char*) ; 

__attribute__((used)) static int parse_args(int argc, char **argv)
{
	const char *optstr = "hlpk:f:r:g:d:";
	int opt;

	while ((opt = getopt(argc, argv, optstr)) != -1) {
		switch (opt) {
		case 'l':
			args.always_log = true;
			break;
		case 'f':
			args.file_test_num = atoi(optarg);
			args.file_test = true;
			break;
		case 'r':
			args.raw_test_num = atoi(optarg);
			args.raw_test = true;
			break;
		case 'g':
			args.get_info_test_num = atoi(optarg);
			args.get_info_test = true;
			break;
		case 'p':
			args.pprint_test = true;
			break;
		case 'k':
			args.info_raw_test_num = atoi(optarg);
			args.info_raw_test = true;
			break;
		case 'd':
			args.dedup_test_num = atoi(optarg);
			args.dedup_test = true;
			break;
		case 'h':
			usage(argv[0]);
			exit(0);
		default:
			usage(argv[0]);
			return -1;
		}
	}

	if (args.raw_test_num &&
	    (args.raw_test_num < 1 ||
	     args.raw_test_num > ARRAY_SIZE(raw_tests))) {
		fprintf(stderr, "BTF raw test number must be [1 - %zu]\n",
			ARRAY_SIZE(raw_tests));
		return -1;
	}

	if (args.file_test_num &&
	    (args.file_test_num < 1 ||
	     args.file_test_num > ARRAY_SIZE(file_tests))) {
		fprintf(stderr, "BTF file test number must be [1 - %zu]\n",
			ARRAY_SIZE(file_tests));
		return -1;
	}

	if (args.get_info_test_num &&
	    (args.get_info_test_num < 1 ||
	     args.get_info_test_num > ARRAY_SIZE(get_info_tests))) {
		fprintf(stderr, "BTF get info test number must be [1 - %zu]\n",
			ARRAY_SIZE(get_info_tests));
		return -1;
	}

	if (args.info_raw_test_num &&
	    (args.info_raw_test_num < 1 ||
	     args.info_raw_test_num > ARRAY_SIZE(info_raw_tests))) {
		fprintf(stderr, "BTF prog info raw test number must be [1 - %zu]\n",
			ARRAY_SIZE(info_raw_tests));
		return -1;
	}

	if (args.dedup_test_num &&
	    (args.dedup_test_num < 1 ||
	     args.dedup_test_num > ARRAY_SIZE(dedup_tests))) {
		fprintf(stderr, "BTF dedup test number must be [1 - %zu]\n",
			ARRAY_SIZE(dedup_tests));
		return -1;
	}

	return 0;
}