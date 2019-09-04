#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ cs_nffree; int /*<<< orphan*/  cs_nbfree; } ;
struct ufs_sb_private_info {TYPE_1__ cs_total; } ;

/* Variables and functions */
 scalar_t__ ufs_blkstofrags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64
ufs_freefrags(struct ufs_sb_private_info *uspi)
{
	return ufs_blkstofrags(uspi->cs_total.cs_nbfree) +
		uspi->cs_total.cs_nffree;
}