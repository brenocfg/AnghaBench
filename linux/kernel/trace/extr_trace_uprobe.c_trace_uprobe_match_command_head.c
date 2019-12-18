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
struct trace_uprobe {int /*<<< orphan*/  tp; int /*<<< orphan*/  ref_ctr_offset; int /*<<< orphan*/  offset; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_ARGSTR_LEN ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int) ; 
 int trace_probe_match_command_args (int /*<<< orphan*/ *,int,char const**) ; 

__attribute__((used)) static bool trace_uprobe_match_command_head(struct trace_uprobe *tu,
					    int argc, const char **argv)
{
	char buf[MAX_ARGSTR_LEN + 1];
	int len;

	if (!argc)
		return true;

	len = strlen(tu->filename);
	if (strncmp(tu->filename, argv[0], len) || argv[0][len] != ':')
		return false;

	if (tu->ref_ctr_offset == 0)
		snprintf(buf, sizeof(buf), "0x%0*lx",
				(int)(sizeof(void *) * 2), tu->offset);
	else
		snprintf(buf, sizeof(buf), "0x%0*lx(0x%lx)",
				(int)(sizeof(void *) * 2), tu->offset,
				tu->ref_ctr_offset);
	if (strcmp(buf, &argv[0][len + 1]))
		return false;

	argc--; argv++;

	return trace_probe_match_command_args(&tu->tp, argc, argv);
}