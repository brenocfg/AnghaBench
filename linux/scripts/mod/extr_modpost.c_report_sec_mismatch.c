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
struct sectioncheck {int mismatch; int /*<<< orphan*/  symbol_white_list; } ;

/* Variables and functions */
#define  ANY_EXIT_TO_ANY_INIT 137 
#define  ANY_INIT_TO_ANY_EXIT 136 
#define  DATA_TO_ANY_EXIT 135 
#define  DATA_TO_ANY_INIT 134 
#define  EXPORT_TO_INIT_EXIT 133 
#define  EXTABLE_TO_NON_TEXT 132 
#define  TEXT_TO_ANY_EXIT 131 
#define  TEXT_TO_ANY_INIT 130 
#define  XXXEXIT_TO_SOME_EXIT 129 
#define  XXXINIT_TO_SOME_INIT 128 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_pretty_name (int,char const**,char const**) ; 
 int /*<<< orphan*/  print_section_list (int /*<<< orphan*/ ) ; 
 char* sec2annotation (char const*) ; 
 int /*<<< orphan*/  sec_mismatch_count ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warn (char*,char const*,char const*,unsigned long long,char const*,char const*,char const*,char const*,char const*,char const*,char const*) ; 

__attribute__((used)) static void report_sec_mismatch(const char *modname,
				const struct sectioncheck *mismatch,
				const char *fromsec,
				unsigned long long fromaddr,
				const char *fromsym,
				int from_is_func,
				const char *tosec, const char *tosym,
				int to_is_func)
{
	const char *from, *from_p;
	const char *to, *to_p;
	char *prl_from;
	char *prl_to;

	sec_mismatch_count++;

	get_pretty_name(from_is_func, &from, &from_p);
	get_pretty_name(to_is_func, &to, &to_p);

	warn("%s(%s+0x%llx): Section mismatch in reference from the %s %s%s "
	     "to the %s %s:%s%s\n",
	     modname, fromsec, fromaddr, from, fromsym, from_p, to, tosec,
	     tosym, to_p);

	switch (mismatch->mismatch) {
	case TEXT_TO_ANY_INIT:
		prl_from = sec2annotation(fromsec);
		prl_to = sec2annotation(tosec);
		fprintf(stderr,
		"The function %s%s() references\n"
		"the %s %s%s%s.\n"
		"This is often because %s lacks a %s\n"
		"annotation or the annotation of %s is wrong.\n",
		prl_from, fromsym,
		to, prl_to, tosym, to_p,
		fromsym, prl_to, tosym);
		free(prl_from);
		free(prl_to);
		break;
	case DATA_TO_ANY_INIT: {
		prl_to = sec2annotation(tosec);
		fprintf(stderr,
		"The variable %s references\n"
		"the %s %s%s%s\n"
		"If the reference is valid then annotate the\n"
		"variable with __init* or __refdata (see linux/init.h) "
		"or name the variable:\n",
		fromsym, to, prl_to, tosym, to_p);
		print_section_list(mismatch->symbol_white_list);
		free(prl_to);
		break;
	}
	case TEXT_TO_ANY_EXIT:
		prl_to = sec2annotation(tosec);
		fprintf(stderr,
		"The function %s() references a %s in an exit section.\n"
		"Often the %s %s%s has valid usage outside the exit section\n"
		"and the fix is to remove the %sannotation of %s.\n",
		fromsym, to, to, tosym, to_p, prl_to, tosym);
		free(prl_to);
		break;
	case DATA_TO_ANY_EXIT: {
		prl_to = sec2annotation(tosec);
		fprintf(stderr,
		"The variable %s references\n"
		"the %s %s%s%s\n"
		"If the reference is valid then annotate the\n"
		"variable with __exit* (see linux/init.h) or "
		"name the variable:\n",
		fromsym, to, prl_to, tosym, to_p);
		print_section_list(mismatch->symbol_white_list);
		free(prl_to);
		break;
	}
	case XXXINIT_TO_SOME_INIT:
	case XXXEXIT_TO_SOME_EXIT:
		prl_from = sec2annotation(fromsec);
		prl_to = sec2annotation(tosec);
		fprintf(stderr,
		"The %s %s%s%s references\n"
		"a %s %s%s%s.\n"
		"If %s is only used by %s then\n"
		"annotate %s with a matching annotation.\n",
		from, prl_from, fromsym, from_p,
		to, prl_to, tosym, to_p,
		tosym, fromsym, tosym);
		free(prl_from);
		free(prl_to);
		break;
	case ANY_INIT_TO_ANY_EXIT:
		prl_from = sec2annotation(fromsec);
		prl_to = sec2annotation(tosec);
		fprintf(stderr,
		"The %s %s%s%s references\n"
		"a %s %s%s%s.\n"
		"This is often seen when error handling "
		"in the init function\n"
		"uses functionality in the exit path.\n"
		"The fix is often to remove the %sannotation of\n"
		"%s%s so it may be used outside an exit section.\n",
		from, prl_from, fromsym, from_p,
		to, prl_to, tosym, to_p,
		prl_to, tosym, to_p);
		free(prl_from);
		free(prl_to);
		break;
	case ANY_EXIT_TO_ANY_INIT:
		prl_from = sec2annotation(fromsec);
		prl_to = sec2annotation(tosec);
		fprintf(stderr,
		"The %s %s%s%s references\n"
		"a %s %s%s%s.\n"
		"This is often seen when error handling "
		"in the exit function\n"
		"uses functionality in the init path.\n"
		"The fix is often to remove the %sannotation of\n"
		"%s%s so it may be used outside an init section.\n",
		from, prl_from, fromsym, from_p,
		to, prl_to, tosym, to_p,
		prl_to, tosym, to_p);
		free(prl_from);
		free(prl_to);
		break;
	case EXPORT_TO_INIT_EXIT:
		prl_to = sec2annotation(tosec);
		fprintf(stderr,
		"The symbol %s is exported and annotated %s\n"
		"Fix this by removing the %sannotation of %s "
		"or drop the export.\n",
		tosym, prl_to, prl_to, tosym);
		free(prl_to);
		break;
	case EXTABLE_TO_NON_TEXT:
		fatal("There's a special handler for this mismatch type, "
		      "we should never get here.");
		break;
	}
	fprintf(stderr, "\n");
}