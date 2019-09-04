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
struct adfs_dir {int nr_buffers; int /*<<< orphan*/ * sb; int /*<<< orphan*/ * bh_fplus; int /*<<< orphan*/ * bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
adfs_fplus_free(struct adfs_dir *dir)
{
	int i;

	if (dir->bh_fplus) {
		for (i = 0; i < dir->nr_buffers; i++)
			brelse(dir->bh_fplus[i]);

		if (&dir->bh[0] != dir->bh_fplus)
			kfree(dir->bh_fplus);

		dir->bh_fplus = NULL;
	}

	dir->nr_buffers = 0;
	dir->sb = NULL;
}