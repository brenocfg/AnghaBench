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
struct debuginfo {scalar_t__ dwfl; int /*<<< orphan*/  dbg; int /*<<< orphan*/  bias; int /*<<< orphan*/  mod; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ dwfl_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwfl_end (scalar_t__) ; 
 int /*<<< orphan*/  dwfl_module_getdwarf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwfl_report_begin (scalar_t__) ; 
 int /*<<< orphan*/  dwfl_report_end (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwfl_report_offline (scalar_t__,char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct debuginfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  offline_callbacks ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int debuginfo__init_offline_dwarf(struct debuginfo *dbg,
					 const char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return fd;

	dbg->dwfl = dwfl_begin(&offline_callbacks);
	if (!dbg->dwfl)
		goto error;

	dwfl_report_begin(dbg->dwfl);
	dbg->mod = dwfl_report_offline(dbg->dwfl, "", "", fd);
	if (!dbg->mod)
		goto error;

	dbg->dbg = dwfl_module_getdwarf(dbg->mod, &dbg->bias);
	if (!dbg->dbg)
		goto error;

	dwfl_report_end(dbg->dwfl, NULL, NULL);

	return 0;
error:
	if (dbg->dwfl)
		dwfl_end(dbg->dwfl);
	else
		close(fd);
	memset(dbg, 0, sizeof(*dbg));

	return -ENOENT;
}