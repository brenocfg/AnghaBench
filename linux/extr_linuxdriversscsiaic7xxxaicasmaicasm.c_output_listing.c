#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* symbol; } ;
typedef  TYPE_3__ symbol_node_t ;
struct TYPE_8__ {int* bytes; } ;
struct instruction {int srcline; TYPE_2__ format; } ;
typedef  int /*<<< orphan*/  patch_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {char* name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_OSERR ; 
 TYPE_3__* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_3__* SLIST_NEXT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct instruction* STAILQ_NEXT (struct instruction*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_patch (int /*<<< orphan*/ **,int,int*,int*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getchar () ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  listfile ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  patch_functions ; 
 int /*<<< orphan*/  patches ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  putchar (int) ; 
 int /*<<< orphan*/  seq_program ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stop (char*,int /*<<< orphan*/ ) ; 
 int toupper (int) ; 

void
output_listing(char *ifilename)
{
	char buf[1024];
	FILE *ifile;
	struct instruction *cur_instr;
	patch_t *cur_patch;
	symbol_node_t *cur_func;
	int *func_values;
	int instrcount;
	int instrptr;
	int line;
	int func_count;
	int skip_addr;

	instrcount = 0;
	instrptr = 0;
	line = 1;
	skip_addr = 0;
	if ((ifile = fopen(ifilename, "r")) == NULL) {
		perror(ifilename);
		stop(NULL, EX_DATAERR);
	}

	/*
	 * Determine which options to apply to this listing.
	 */
	for (func_count = 0, cur_func = SLIST_FIRST(&patch_functions);
	    cur_func != NULL;
	    cur_func = SLIST_NEXT(cur_func, links))
		func_count++;

	func_values = NULL;
	if (func_count != 0) {
		func_values = (int *)malloc(func_count * sizeof(int));

		if (func_values == NULL)
			stop("Could not malloc", EX_OSERR);
		
		func_values[0] = 0; /* FALSE func */
		func_count--;

		/*
		 * Ask the user to fill in the return values for
		 * the rest of the functions.
		 */
		
		
		for (cur_func = SLIST_FIRST(&patch_functions);
		     cur_func != NULL && SLIST_NEXT(cur_func, links) != NULL;
		     cur_func = SLIST_NEXT(cur_func, links), func_count--) {
			int input;
			
			fprintf(stdout, "\n(%s)\n", cur_func->symbol->name);
			fprintf(stdout,
				"Enter the return value for "
				"this expression[T/F]:");

			while (1) {

				input = getchar();
				input = toupper(input);

				if (input == 'T') {
					func_values[func_count] = 1;
					break;
				} else if (input == 'F') {
					func_values[func_count] = 0;
					break;
				}
			}
			if (isatty(fileno(stdin)) == 0)
				putchar(input);
		}
		fprintf(stdout, "\nThanks!\n");
	}

	/* Now output the listing */
	cur_patch = STAILQ_FIRST(&patches);
	for (cur_instr = STAILQ_FIRST(&seq_program);
	     cur_instr != NULL;
	     cur_instr = STAILQ_NEXT(cur_instr, links), instrcount++) {

		if (check_patch(&cur_patch, instrcount,
				&skip_addr, func_values) == 0) {
			/* Don't count this instruction as it is in a patch
			 * that was removed.
			 */
                        continue;
		}

		while (line < cur_instr->srcline) {
			fgets(buf, sizeof(buf), ifile);
				fprintf(listfile, "             \t%s", buf);
				line++;
		}
		fprintf(listfile, "%04x %02x%02x%02x%02x", instrptr,
#ifdef __LITTLE_ENDIAN
			cur_instr->format.bytes[0],
			cur_instr->format.bytes[1],
			cur_instr->format.bytes[2],
			cur_instr->format.bytes[3]);
#else
			cur_instr->format.bytes[3],
			cur_instr->format.bytes[2],
			cur_instr->format.bytes[1],
			cur_instr->format.bytes[0]);
#endif
		/*
		 * Macro expansions can cause several instructions
		 * to be output for a single source line.  Only
		 * advance the line once in these cases.
		 */
		if (line == cur_instr->srcline) {
			fgets(buf, sizeof(buf), ifile);
			fprintf(listfile, "\t%s", buf);
			line++;
		} else {
			fprintf(listfile, "\n");
		}
		instrptr++;
	}
	/* Dump the remainder of the file */
	while(fgets(buf, sizeof(buf), ifile) != NULL)
		fprintf(listfile, "             %s", buf);

	fclose(ifile);
}