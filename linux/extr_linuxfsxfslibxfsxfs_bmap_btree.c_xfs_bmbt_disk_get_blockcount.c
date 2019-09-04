#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_filblks_t ;
struct TYPE_3__ {int /*<<< orphan*/  l1; } ;
typedef  TYPE_1__ xfs_bmbt_rec_t ;

/* Variables and functions */
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 int xfs_mask64lo (int) ; 

xfs_filblks_t
xfs_bmbt_disk_get_blockcount(
	xfs_bmbt_rec_t	*r)
{
	return (xfs_filblks_t)(be64_to_cpu(r->l1) & xfs_mask64lo(21));
}