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
struct nfs4_ff_layout_mirror {int fh_versions_cnt; int /*<<< orphan*/ * fh_versions; } ;

/* Variables and functions */
 scalar_t__ nfs_compare_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ff_mirror_match_fh(const struct nfs4_ff_layout_mirror *m1,
		const struct nfs4_ff_layout_mirror *m2)
{
	int i, j;

	if (m1->fh_versions_cnt != m2->fh_versions_cnt)
		return false;
	for (i = 0; i < m1->fh_versions_cnt; i++) {
		bool found_fh = false;
		for (j = 0; j < m2->fh_versions_cnt; j++) {
			if (nfs_compare_fh(&m1->fh_versions[i],
					&m2->fh_versions[j]) == 0) {
				found_fh = true;
				break;
			}
		}
		if (!found_fh)
			return false;
	}
	return true;
}