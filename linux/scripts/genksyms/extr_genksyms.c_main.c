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
struct symbol {size_t type; char* name; struct symbol* visited; int /*<<< orphan*/  defn; scalar_t__ is_extern; scalar_t__ is_override; } ;
struct option {char* member_0; int member_1; char member_3; int /*<<< orphan*/  member_2; } ;
struct TYPE_2__ {char n; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int HASH_BUCKETS ; 
 int /*<<< orphan*/ * debugfile ; 
 scalar_t__ errors ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int flag_debug ; 
 int flag_dump_defs ; 
 int flag_dump_types ; 
 int flag_preserve ; 
 int flag_reference ; 
 int flag_rel_crcs ; 
 int flag_warnings ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,double) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genksyms_usage () ; 
 int getopt (int,char**,char*) ; 
 int getopt_long (int,char**,char*,struct option*,int /*<<< orphan*/ *) ; 
 int nsyms ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stderr ; 
 TYPE_1__* symbol_types ; 
 struct symbol* visited_symbols ; 
 int /*<<< orphan*/  yyparse () ; 

int main(int argc, char **argv)
{
	FILE *dumpfile = NULL, *ref_file = NULL;
	int o;

#ifdef __GNU_LIBRARY__
	struct option long_opts[] = {
		{"debug", 0, 0, 'd'},
		{"warnings", 0, 0, 'w'},
		{"quiet", 0, 0, 'q'},
		{"dump", 0, 0, 'D'},
		{"reference", 1, 0, 'r'},
		{"dump-types", 1, 0, 'T'},
		{"preserve", 0, 0, 'p'},
		{"version", 0, 0, 'V'},
		{"help", 0, 0, 'h'},
		{"relative-crc", 0, 0, 'R'},
		{0, 0, 0, 0}
	};

	while ((o = getopt_long(argc, argv, "s:dwqVDr:T:phR",
				&long_opts[0], NULL)) != EOF)
#else				/* __GNU_LIBRARY__ */
	while ((o = getopt(argc, argv, "s:dwqVDr:T:phR")) != EOF)
#endif				/* __GNU_LIBRARY__ */
		switch (o) {
		case 'd':
			flag_debug++;
			break;
		case 'w':
			flag_warnings = 1;
			break;
		case 'q':
			flag_warnings = 0;
			break;
		case 'V':
			fputs("genksyms version 2.5.60\n", stderr);
			break;
		case 'D':
			flag_dump_defs = 1;
			break;
		case 'r':
			flag_reference = 1;
			ref_file = fopen(optarg, "r");
			if (!ref_file) {
				perror(optarg);
				return 1;
			}
			break;
		case 'T':
			flag_dump_types = 1;
			dumpfile = fopen(optarg, "w");
			if (!dumpfile) {
				perror(optarg);
				return 1;
			}
			break;
		case 'p':
			flag_preserve = 1;
			break;
		case 'h':
			genksyms_usage();
			return 0;
		case 'R':
			flag_rel_crcs = 1;
			break;
		default:
			genksyms_usage();
			return 1;
		}
	{
		extern int yydebug;
		extern int yy_flex_debug;

		yydebug = (flag_debug > 1);
		yy_flex_debug = (flag_debug > 2);

		debugfile = stderr;
		/* setlinebuf(debugfile); */
	}

	if (flag_reference) {
		read_reference(ref_file);
		fclose(ref_file);
	}

	yyparse();

	if (flag_dump_types && visited_symbols) {
		while (visited_symbols != (struct symbol *)-1L) {
			struct symbol *sym = visited_symbols;

			if (sym->is_override)
				fputs("override ", dumpfile);
			if (symbol_types[sym->type].n) {
				putc(symbol_types[sym->type].n, dumpfile);
				putc('#', dumpfile);
			}
			fputs(sym->name, dumpfile);
			putc(' ', dumpfile);
			if (sym->is_extern)
				fputs("extern ", dumpfile);
			print_list(dumpfile, sym->defn);
			putc('\n', dumpfile);

			visited_symbols = sym->visited;
			sym->visited = NULL;
		}
	}

	if (flag_debug) {
		fprintf(debugfile, "Hash table occupancy %d/%d = %g\n",
			nsyms, HASH_BUCKETS,
			(double)nsyms / (double)HASH_BUCKETS);
	}

	if (dumpfile)
		fclose(dumpfile);

	return errors != 0;
}