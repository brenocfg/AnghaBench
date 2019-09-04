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
struct metapath {int /*<<< orphan*/ ** mp_bh; } ;

/* Variables and functions */
 int GFS2_MAX_META_HEIGHT ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_metapath(struct metapath *mp)
{
	int i;

	for (i = 0; i < GFS2_MAX_META_HEIGHT; i++) {
		if (mp->mp_bh[i] == NULL)
			break;
		brelse(mp->mp_bh[i]);
		mp->mp_bh[i] = NULL;
	}
}