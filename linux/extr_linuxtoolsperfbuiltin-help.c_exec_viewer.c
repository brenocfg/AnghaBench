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

/* Variables and functions */
 int /*<<< orphan*/  exec_man_cmd (char const*,char const*) ; 
 int /*<<< orphan*/  exec_man_konqueror (char const*,char const*) ; 
 int /*<<< orphan*/  exec_man_man (char const*,char const*) ; 
 int /*<<< orphan*/  exec_woman_emacs (char const*,char const*) ; 
 char* get_man_viewer_info (char const*) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static void exec_viewer(const char *name, const char *page)
{
	const char *info = get_man_viewer_info(name);

	if (!strcasecmp(name, "man"))
		exec_man_man(info, page);
	else if (!strcasecmp(name, "woman"))
		exec_woman_emacs(info, page);
	else if (!strcasecmp(name, "konqueror"))
		exec_man_konqueror(info, page);
	else if (info)
		exec_man_cmd(info, page);
	else
		pr_warning("'%s': unknown man viewer.", name);
}