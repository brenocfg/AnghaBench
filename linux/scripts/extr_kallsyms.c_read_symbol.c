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
struct sym_entry {char* sym; int /*<<< orphan*/  addr; scalar_t__ percpu_absolute; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EOF ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ KSYM_NAME_LEN ; 
 int /*<<< orphan*/  _text ; 
 scalar_t__ check_symbol_range (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ is_arm_mapping_symbol (char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  percpu_range ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/ * text_ranges ; 
 unsigned char toupper (char) ; 

__attribute__((used)) static int read_symbol(FILE *in, struct sym_entry *s)
{
	char sym[500], stype;
	int rc;

	rc = fscanf(in, "%llx %c %499s\n", &s->addr, &stype, sym);
	if (rc != 3) {
		if (rc != EOF && fgets(sym, 500, in) == NULL)
			fprintf(stderr, "Read error or end of file.\n");
		return -1;
	}
	if (strlen(sym) >= KSYM_NAME_LEN) {
		fprintf(stderr, "Symbol %s too long for kallsyms (%zu >= %d).\n"
				"Please increase KSYM_NAME_LEN both in kernel and kallsyms.c\n",
			sym, strlen(sym), KSYM_NAME_LEN);
		return -1;
	}

	/* Ignore most absolute/undefined (?) symbols. */
	if (strcmp(sym, "_text") == 0)
		_text = s->addr;
	else if (check_symbol_range(sym, s->addr, text_ranges,
				    ARRAY_SIZE(text_ranges)) == 0)
		/* nothing to do */;
	else if (toupper(stype) == 'A')
	{
		/* Keep these useful absolute symbols */
		if (strcmp(sym, "__kernel_syscall_via_break") &&
		    strcmp(sym, "__kernel_syscall_via_epc") &&
		    strcmp(sym, "__kernel_sigtramp") &&
		    strcmp(sym, "__gp"))
			return -1;

	}
	else if (toupper(stype) == 'U' ||
		 is_arm_mapping_symbol(sym))
		return -1;
	/* exclude also MIPS ELF local symbols ($L123 instead of .L123) */
	else if (sym[0] == '$')
		return -1;
	/* exclude debugging symbols */
	else if (stype == 'N' || stype == 'n')
		return -1;
	/* exclude s390 kasan local symbols */
	else if (!strncmp(sym, ".LASANPC", 8))
		return -1;

	/* include the type field in the symbol name, so that it gets
	 * compressed together */
	s->len = strlen(sym) + 1;
	s->sym = malloc(s->len + 1);
	if (!s->sym) {
		fprintf(stderr, "kallsyms failure: "
			"unable to allocate required amount of memory\n");
		exit(EXIT_FAILURE);
	}
	strcpy((char *)s->sym + 1, sym);
	s->sym[0] = stype;

	s->percpu_absolute = 0;

	/* Record if we've found __per_cpu_start/end. */
	check_symbol_range(sym, s->addr, &percpu_range, 1);

	return 0;
}