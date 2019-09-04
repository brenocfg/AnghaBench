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
struct metapath {unsigned int mp_aheight; int /*<<< orphan*/ * mp_bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_bh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clone_metapath(struct metapath *clone, struct metapath *mp)
{
	unsigned int hgt;

	*clone = *mp;
	for (hgt = 0; hgt < mp->mp_aheight; hgt++)
		get_bh(clone->mp_bh[hgt]);
}