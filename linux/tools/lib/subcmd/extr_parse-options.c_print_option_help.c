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
struct option {int type; char* help; int flags; int short_name; char* long_name; char* argh; char* build_opt; } ;

/* Variables and functions */
#define  OPTION_ARGUMENT 142 
#define  OPTION_BIT 141 
#define  OPTION_BOOLEAN 140 
#define  OPTION_CALLBACK 139 
#define  OPTION_END 138 
#define  OPTION_GROUP 137 
#define  OPTION_INCR 136 
#define  OPTION_INTEGER 135 
#define  OPTION_LONG 134 
#define  OPTION_SET_PTR 133 
#define  OPTION_SET_UINT 132 
#define  OPTION_STRING 131 
#define  OPTION_U64 130 
#define  OPTION_UINTEGER 129 
#define  OPTION_ULONG 128 
 int PARSE_OPT_DISABLED ; 
 int PARSE_OPT_HIDDEN ; 
 int PARSE_OPT_NOARG ; 
 int PARSE_OPT_NOBUILD ; 
 int PARSE_OPT_OPTARG ; 
 char* USAGE_GAP ; 
 size_t USAGE_OPTS_WIDTH ; 
 size_t fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void print_option_help(const struct option *opts, int full)
{
	size_t pos;
	int pad;

	if (opts->type == OPTION_GROUP) {
		fputc('\n', stderr);
		if (*opts->help)
			fprintf(stderr, "%s\n", opts->help);
		return;
	}
	if (!full && (opts->flags & PARSE_OPT_HIDDEN))
		return;
	if (opts->flags & PARSE_OPT_DISABLED)
		return;

	pos = fprintf(stderr, "    ");
	if (opts->short_name)
		pos += fprintf(stderr, "-%c", opts->short_name);
	else
		pos += fprintf(stderr, "    ");

	if (opts->long_name && opts->short_name)
		pos += fprintf(stderr, ", ");
	if (opts->long_name)
		pos += fprintf(stderr, "--%s", opts->long_name);

	switch (opts->type) {
	case OPTION_ARGUMENT:
		break;
	case OPTION_LONG:
	case OPTION_ULONG:
	case OPTION_U64:
	case OPTION_INTEGER:
	case OPTION_UINTEGER:
		if (opts->flags & PARSE_OPT_OPTARG)
			if (opts->long_name)
				pos += fprintf(stderr, "[=<n>]");
			else
				pos += fprintf(stderr, "[<n>]");
		else
			pos += fprintf(stderr, " <n>");
		break;
	case OPTION_CALLBACK:
		if (opts->flags & PARSE_OPT_NOARG)
			break;
		/* FALLTHROUGH */
	case OPTION_STRING:
		if (opts->argh) {
			if (opts->flags & PARSE_OPT_OPTARG)
				if (opts->long_name)
					pos += fprintf(stderr, "[=<%s>]", opts->argh);
				else
					pos += fprintf(stderr, "[<%s>]", opts->argh);
			else
				pos += fprintf(stderr, " <%s>", opts->argh);
		} else {
			if (opts->flags & PARSE_OPT_OPTARG)
				if (opts->long_name)
					pos += fprintf(stderr, "[=...]");
				else
					pos += fprintf(stderr, "[...]");
			else
				pos += fprintf(stderr, " ...");
		}
		break;
	default: /* OPTION_{BIT,BOOLEAN,SET_UINT,SET_PTR} */
	case OPTION_END:
	case OPTION_GROUP:
	case OPTION_BIT:
	case OPTION_BOOLEAN:
	case OPTION_INCR:
	case OPTION_SET_UINT:
	case OPTION_SET_PTR:
		break;
	}

	if (pos <= USAGE_OPTS_WIDTH)
		pad = USAGE_OPTS_WIDTH - pos;
	else {
		fputc('\n', stderr);
		pad = USAGE_OPTS_WIDTH;
	}
	fprintf(stderr, "%*s%s\n", pad + USAGE_GAP, "", opts->help);
	if (opts->flags & PARSE_OPT_NOBUILD)
		fprintf(stderr, "%*s(not built-in because %s)\n",
			USAGE_OPTS_WIDTH + USAGE_GAP, "",
			opts->build_opt);
}