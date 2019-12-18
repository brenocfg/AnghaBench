#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct probe_finder {TYPE_2__* pev; int /*<<< orphan*/  lcache; int /*<<< orphan*/  fname; int /*<<< orphan*/  cu_die; } ;
struct TYPE_3__ {int /*<<< orphan*/  lazy_line; } ;
struct TYPE_4__ {TYPE_1__ point; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 char* cu_get_comp_dir (int /*<<< orphan*/ *) ; 
 int die_walk_lines (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct probe_finder*) ; 
 int find_lazy_match_lines (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_real_path (int /*<<< orphan*/ ,char const*,char**) ; 
 scalar_t__ intlist__empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  probe_point_lazy_walker ; 

__attribute__((used)) static int find_probe_point_lazy(Dwarf_Die *sp_die, struct probe_finder *pf)
{
	int ret = 0;
	char *fpath;

	if (intlist__empty(pf->lcache)) {
		const char *comp_dir;

		comp_dir = cu_get_comp_dir(&pf->cu_die);
		ret = get_real_path(pf->fname, comp_dir, &fpath);
		if (ret < 0) {
			pr_warning("Failed to find source file path.\n");
			return ret;
		}

		/* Matching lazy line pattern */
		ret = find_lazy_match_lines(pf->lcache, fpath,
					    pf->pev->point.lazy_line);
		free(fpath);
		if (ret <= 0)
			return ret;
	}

	return die_walk_lines(sp_die, probe_point_lazy_walker, pf);
}