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
struct stat {int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 int /*<<< orphan*/  opt_cgroup ; 
 int /*<<< orphan*/  parse_number (char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static void parse_cgroup(const char *path)
{
	if (path[0] == '@') {
		opt_cgroup = parse_number(path + 1);
		return;
	}

	struct stat st;

	if (stat(path, &st))
		fatal("stat failed: %s: %m\n", path);

	if (!S_ISDIR(st.st_mode))
		fatal("cgroup supposed to be a directory: %s\n", path);

	opt_cgroup = st.st_ino;
}