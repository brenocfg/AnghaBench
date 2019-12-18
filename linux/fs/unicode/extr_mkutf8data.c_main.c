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
struct TYPE_2__ {unsigned int code; } ;

/* Variables and functions */
 int /*<<< orphan*/  age_init () ; 
 void* age_name ; 
 char* argv0 ; 
 int /*<<< orphan*/  ccc_init () ; 
 void* ccc_name ; 
 int /*<<< orphan*/  corrections_init () ; 
 void* data_name ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 void* fold_name ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  hangul_decompose () ; 
 int /*<<< orphan*/  help () ; 
 int /*<<< orphan*/  ignore_init () ; 
 int /*<<< orphan*/  lookup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nfdi_decompose () ; 
 int /*<<< orphan*/  nfdi_init () ; 
 int /*<<< orphan*/  nfdi_tree ; 
 int /*<<< orphan*/  nfdicf_decompose () ; 
 int /*<<< orphan*/  nfdicf_init () ; 
 int /*<<< orphan*/  nfdicf_tree ; 
 void* norm_name ; 
 int /*<<< orphan*/  normalization_test () ; 
 void* optarg ; 
 void* prop_name ; 
 void* test_name ; 
 int /*<<< orphan*/  tree_walk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trees_init () ; 
 int /*<<< orphan*/  trees_populate () ; 
 int /*<<< orphan*/  trees_reduce () ; 
 int /*<<< orphan*/  trees_verify () ; 
 TYPE_1__* unicode_data ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  utf8_init () ; 
 void* utf8_name ; 
 int verbose ; 
 int /*<<< orphan*/  write_file () ; 

int main(int argc, char *argv[])
{
	unsigned int unichar;
	int opt;

	argv0 = argv[0];

	while ((opt = getopt(argc, argv, "a:c:d:f:hn:o:p:t:v")) != -1) {
		switch (opt) {
		case 'a':
			age_name = optarg;
			break;
		case 'c':
			ccc_name = optarg;
			break;
		case 'd':
			data_name = optarg;
			break;
		case 'f':
			fold_name = optarg;
			break;
		case 'n':
			norm_name = optarg;
			break;
		case 'o':
			utf8_name = optarg;
			break;
		case 'p':
			prop_name = optarg;
			break;
		case 't':
			test_name = optarg;
			break;
		case 'v':
			verbose++;
			break;
		case 'h':
			help();
			exit(0);
		default:
			usage();
		}
	}

	if (verbose > 1)
		help();
	for (unichar = 0; unichar != 0x110000; unichar++)
		unicode_data[unichar].code = unichar;
	age_init();
	ccc_init();
	nfdi_init();
	nfdicf_init();
	ignore_init();
	corrections_init();
	hangul_decompose();
	nfdi_decompose();
	nfdicf_decompose();
	utf8_init();
	trees_init();
	trees_populate();
	trees_reduce();
	trees_verify();
	/* Prevent "unused function" warning. */
	(void)lookup(nfdi_tree, " ");
	if (verbose > 2)
		tree_walk(nfdi_tree);
	if (verbose > 2)
		tree_walk(nfdicf_tree);
	normalization_test();
	write_file();

	return 0;
}