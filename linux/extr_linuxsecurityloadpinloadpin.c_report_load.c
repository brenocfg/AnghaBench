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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup_quotable_cmdline (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kstrdup_quotable_file (struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,char const*,char*,char*,char*,char*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void report_load(const char *origin, struct file *file, char *operation)
{
	char *cmdline, *pathname;

	pathname = kstrdup_quotable_file(file, GFP_KERNEL);
	cmdline = kstrdup_quotable_cmdline(current, GFP_KERNEL);

	pr_notice("%s %s obj=%s%s%s pid=%d cmdline=%s%s%s\n",
		  origin, operation,
		  (pathname && pathname[0] != '<') ? "\"" : "",
		  pathname,
		  (pathname && pathname[0] != '<') ? "\"" : "",
		  task_pid_nr(current),
		  cmdline ? "\"" : "", cmdline, cmdline ? "\"" : "");

	kfree(cmdline);
	kfree(pathname);
}