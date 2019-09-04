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
struct perf_probe_point {char* function; char* file; int retprobe; int /*<<< orphan*/ * lazy_line; void* offset; void* line; void* abs_address; } ;
struct perf_probe_event {int sdt; int /*<<< orphan*/  event; struct perf_probe_point point; void* target; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 char* build_id_cache__complement (char*) ; 
 void* build_id_cache__origname (char*) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_sdt_event (char*) ; 
 scalar_t__ memchr (char*,char,int) ; 
 int parse_perf_probe_event_name (char**,struct perf_probe_event*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,char*,void*,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char*,int) ; 
 int /*<<< orphan*/  semantic_error (char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 void* strdup_esc (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strpbrk_esc (char*,char*) ; 
 void* strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_perf_probe_point(char *arg, struct perf_probe_event *pev)
{
	struct perf_probe_point *pp = &pev->point;
	char *ptr, *tmp;
	char c, nc = 0;
	bool file_spec = false;
	int ret;

	/*
	 * <Syntax>
	 * perf probe [GRP:][EVENT=]SRC[:LN|;PTN]
	 * perf probe [GRP:][EVENT=]FUNC[@SRC][+OFFS|%return|:LN|;PAT]
	 * perf probe %[GRP:]SDT_EVENT
	 */
	if (!arg)
		return -EINVAL;

	if (is_sdt_event(arg)) {
		pev->sdt = true;
		if (arg[0] == '%')
			arg++;
	}

	ptr = strpbrk_esc(arg, ";=@+%");
	if (pev->sdt) {
		if (ptr) {
			if (*ptr != '@') {
				semantic_error("%s must be an SDT name.\n",
					       arg);
				return -EINVAL;
			}
			/* This must be a target file name or build id */
			tmp = build_id_cache__complement(ptr + 1);
			if (tmp) {
				pev->target = build_id_cache__origname(tmp);
				free(tmp);
			} else
				pev->target = strdup_esc(ptr + 1);
			if (!pev->target)
				return -ENOMEM;
			*ptr = '\0';
		}
		ret = parse_perf_probe_event_name(&arg, pev);
		if (ret == 0) {
			if (asprintf(&pev->point.function, "%%%s", pev->event) < 0)
				ret = -errno;
		}
		return ret;
	}

	if (ptr && *ptr == '=') {	/* Event name */
		*ptr = '\0';
		tmp = ptr + 1;
		ret = parse_perf_probe_event_name(&arg, pev);
		if (ret < 0)
			return ret;

		arg = tmp;
	}

	/*
	 * Check arg is function or file name and copy it.
	 *
	 * We consider arg to be a file spec if and only if it satisfies
	 * all of the below criteria::
	 * - it does not include any of "+@%",
	 * - it includes one of ":;", and
	 * - it has a period '.' in the name.
	 *
	 * Otherwise, we consider arg to be a function specification.
	 */
	if (!strpbrk_esc(arg, "+@%")) {
		ptr = strpbrk_esc(arg, ";:");
		/* This is a file spec if it includes a '.' before ; or : */
		if (ptr && memchr(arg, '.', ptr - arg))
			file_spec = true;
	}

	ptr = strpbrk_esc(arg, ";:+@%");
	if (ptr) {
		nc = *ptr;
		*ptr++ = '\0';
	}

	if (arg[0] == '\0')
		tmp = NULL;
	else {
		tmp = strdup_esc(arg);
		if (tmp == NULL)
			return -ENOMEM;
	}

	if (file_spec)
		pp->file = tmp;
	else {
		pp->function = tmp;

		/*
		 * Keep pp->function even if this is absolute address,
		 * so it can mark whether abs_address is valid.
		 * Which make 'perf probe lib.bin 0x0' possible.
		 *
		 * Note that checking length of tmp is not needed
		 * because when we access tmp[1] we know tmp[0] is '0',
		 * so tmp[1] should always valid (but could be '\0').
		 */
		if (tmp && !strncmp(tmp, "0x", 2)) {
			pp->abs_address = strtoul(pp->function, &tmp, 0);
			if (*tmp != '\0') {
				semantic_error("Invalid absolute address.\n");
				return -EINVAL;
			}
		}
	}

	/* Parse other options */
	while (ptr) {
		arg = ptr;
		c = nc;
		if (c == ';') {	/* Lazy pattern must be the last part */
			pp->lazy_line = strdup(arg); /* let leave escapes */
			if (pp->lazy_line == NULL)
				return -ENOMEM;
			break;
		}
		ptr = strpbrk_esc(arg, ";:+@%");
		if (ptr) {
			nc = *ptr;
			*ptr++ = '\0';
		}
		switch (c) {
		case ':':	/* Line number */
			pp->line = strtoul(arg, &tmp, 0);
			if (*tmp != '\0') {
				semantic_error("There is non-digit char"
					       " in line number.\n");
				return -EINVAL;
			}
			break;
		case '+':	/* Byte offset from a symbol */
			pp->offset = strtoul(arg, &tmp, 0);
			if (*tmp != '\0') {
				semantic_error("There is non-digit character"
						" in offset.\n");
				return -EINVAL;
			}
			break;
		case '@':	/* File name */
			if (pp->file) {
				semantic_error("SRC@SRC is not allowed.\n");
				return -EINVAL;
			}
			pp->file = strdup_esc(arg);
			if (pp->file == NULL)
				return -ENOMEM;
			break;
		case '%':	/* Probe places */
			if (strcmp(arg, "return") == 0) {
				pp->retprobe = 1;
			} else {	/* Others not supported yet */
				semantic_error("%%%s is not supported.\n", arg);
				return -ENOTSUP;
			}
			break;
		default:	/* Buggy case */
			pr_err("This program has a bug at %s:%d.\n",
				__FILE__, __LINE__);
			return -ENOTSUP;
			break;
		}
	}

	/* Exclusion check */
	if (pp->lazy_line && pp->line) {
		semantic_error("Lazy pattern can't be used with"
			       " line number.\n");
		return -EINVAL;
	}

	if (pp->lazy_line && pp->offset) {
		semantic_error("Lazy pattern can't be used with offset.\n");
		return -EINVAL;
	}

	if (pp->line && pp->offset) {
		semantic_error("Offset can't be used with line number.\n");
		return -EINVAL;
	}

	if (!pp->line && !pp->lazy_line && pp->file && !pp->function) {
		semantic_error("File always requires line number or "
			       "lazy pattern.\n");
		return -EINVAL;
	}

	if (pp->offset && !pp->function) {
		semantic_error("Offset requires an entry function.\n");
		return -EINVAL;
	}

	if ((pp->offset || pp->line || pp->lazy_line) && pp->retprobe) {
		semantic_error("Offset/Line/Lazy pattern can't be used with "
			       "return probe.\n");
		return -EINVAL;
	}

	pr_debug("symbol:%s file:%s line:%d offset:%lu return:%d lazy:%s\n",
		 pp->function, pp->file, pp->line, pp->offset, pp->retprobe,
		 pp->lazy_line);
	return 0;
}