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
struct group_info {int ngroups; int /*<<< orphan*/ * gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool groups_equal(struct group_info *g1, struct group_info *g2)
{
	int i;

	if (g1->ngroups != g2->ngroups)
		return false;
	for (i=0; i<g1->ngroups; i++)
		if (!gid_eq(g1->gid[i], g2->gid[i]))
			return false;
	return true;
}