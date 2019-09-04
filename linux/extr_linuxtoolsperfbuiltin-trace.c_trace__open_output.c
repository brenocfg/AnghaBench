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
struct trace {int /*<<< orphan*/ * output; } ;
struct stat {scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  oldname ;

/* Variables and functions */
 int PATH_MAX ; 
 int errno ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  rename (char const*,char*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int trace__open_output(struct trace *trace, const char *filename)
{
	struct stat st;

	if (!stat(filename, &st) && st.st_size) {
		char oldname[PATH_MAX];

		scnprintf(oldname, sizeof(oldname), "%s.old", filename);
		unlink(oldname);
		rename(filename, oldname);
	}

	trace->output = fopen(filename, "w");

	return trace->output == NULL ? -errno : 0;
}