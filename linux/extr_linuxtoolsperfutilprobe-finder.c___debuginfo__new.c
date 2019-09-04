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
struct debuginfo {int dummy; } ;

/* Variables and functions */
 scalar_t__ debuginfo__init_offline_dwarf (struct debuginfo*,char const*) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 struct debuginfo* zalloc (int) ; 
 int /*<<< orphan*/  zfree (struct debuginfo**) ; 

__attribute__((used)) static struct debuginfo *__debuginfo__new(const char *path)
{
	struct debuginfo *dbg = zalloc(sizeof(*dbg));
	if (!dbg)
		return NULL;

	if (debuginfo__init_offline_dwarf(dbg, path) < 0)
		zfree(&dbg);
	if (dbg)
		pr_debug("Open Debuginfo file: %s\n", path);
	return dbg;
}