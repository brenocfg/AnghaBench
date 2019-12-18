#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct option {char* member_0; float member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  const member_1; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* print_gvars ) (TYPE_1__*,int /*<<< orphan*/ ,char) ;int /*<<< orphan*/  (* print_types ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pdb_parse ) (TYPE_1__*) ;int /*<<< orphan*/  file_name; } ;
typedef  TYPE_1__ R_PDB ;

/* Variables and functions */
 int getopt_long (int,char**,char*,struct option*,int*) ; 
 int /*<<< orphan*/  init_pdb_parser (TYPE_1__*) ; 
#define  no_argument 129 
 char* optarg ; 
 int /*<<< orphan*/  print_usage () ; 
 int /*<<< orphan*/  printf (char*) ; 
#define  required_argument 128 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,char) ; 

int main(int argc, char **argv) {
	R_PDB pdb;

	static struct option long_options[] =
	{
		{"pdb_file", required_argument, 0, 'f'},
		{"print_types", no_argument, 0, 't'},
		{"print_globals", required_argument, 0, 'g'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};

	int option_index = 0;
	int c = 0;
	char *pdb_file = 0;

	while(1) {
		c = getopt_long (argc, argv, ":f:tg:h",
						 long_options, &option_index);

		if (c == -1)
			break;

		switch (c) {
		case 'f':
			pdb_file = optarg;
			strcpy (&pdb.file_name, optarg);
			if (!init_pdb_parser(&pdb)) {
				printf("initialization error of pdb parser\n");
				return 0;
			}
			pdb.pdb_parse(&pdb);
			break;
		case 't':
			pdb.print_types(&pdb, 0);
			break;
		case 'g':
			pdb.print_gvars(&pdb, 0, 'r'); //*(int *)optarg);
			break;
		default:
			print_usage();
			return 0;
		}
	}

	return 0;
}