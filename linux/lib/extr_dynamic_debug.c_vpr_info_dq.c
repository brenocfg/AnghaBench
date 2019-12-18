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
struct ddebug_query {char* format; char* function; char* filename; char* module; int /*<<< orphan*/  last_lineno; int /*<<< orphan*/  first_lineno; } ;

/* Variables and functions */
 int strlen (char*) ; 
 int /*<<< orphan*/  vpr_info (char*,char const*,char*,char*,char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vpr_info_dq(const struct ddebug_query *query, const char *msg)
{
	/* trim any trailing newlines */
	int fmtlen = 0;

	if (query->format) {
		fmtlen = strlen(query->format);
		while (fmtlen && query->format[fmtlen - 1] == '\n')
			fmtlen--;
	}

	vpr_info("%s: func=\"%s\" file=\"%s\" module=\"%s\" format=\"%.*s\" lineno=%u-%u\n",
		 msg,
		 query->function ? query->function : "",
		 query->filename ? query->filename : "",
		 query->module ? query->module : "",
		 fmtlen, query->format ? query->format : "",
		 query->first_lineno, query->last_lineno);
}