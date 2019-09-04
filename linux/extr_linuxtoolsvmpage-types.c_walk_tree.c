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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct FTW {int dummy; } ;

/* Variables and functions */
#define  FTW_DNR 129 
#define  FTW_F 128 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  walk_file (char const*,struct stat const*) ; 

int walk_tree(const char *name, const struct stat *st, int type, struct FTW *f)
{
	(void)f;
	switch (type) {
	case FTW_F:
		if (S_ISREG(st->st_mode))
			walk_file(name, st);
		break;
	case FTW_DNR:
		fprintf(stderr, "cannot read dir: %s\n", name);
		break;
	}
	return 0;
}