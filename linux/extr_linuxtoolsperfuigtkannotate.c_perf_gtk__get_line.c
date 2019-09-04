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
struct TYPE_2__ {scalar_t__ offset; int /*<<< orphan*/  line; } ;
struct disasm_line {TYPE_1__ al; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_markup_escape_text (int /*<<< orphan*/ ,int) ; 
 scalar_t__ scnprintf (char*,size_t,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int perf_gtk__get_line(char *buf, size_t size, struct disasm_line *dl)
{
	int ret = 0;
	char *line = g_markup_escape_text(dl->al.line, -1);
	const char *markup = "<span fgcolor='gray'>";

	strcpy(buf, "");

	if (!line)
		return 0;

	if (dl->al.offset != (s64) -1)
		markup = NULL;

	if (markup)
		ret += scnprintf(buf, size, "%s", markup);
	ret += scnprintf(buf + ret, size - ret, "%s", line);
	if (markup)
		ret += scnprintf(buf + ret, size - ret, "</span>");

	g_free(line);
	return ret;
}