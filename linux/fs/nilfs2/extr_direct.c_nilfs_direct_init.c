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
struct nilfs_bmap {int /*<<< orphan*/ * b_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  nilfs_direct_ops ; 

int nilfs_direct_init(struct nilfs_bmap *bmap)
{
	bmap->b_ops = &nilfs_direct_ops;
	return 0;
}