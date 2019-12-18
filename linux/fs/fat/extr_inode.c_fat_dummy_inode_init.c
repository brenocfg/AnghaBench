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
struct inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ i_pos; scalar_t__ i_attrs; scalar_t__ i_logstart; scalar_t__ i_start; scalar_t__ mmu_private; } ;

/* Variables and functions */
 TYPE_1__* MSDOS_I (struct inode*) ; 

__attribute__((used)) static void fat_dummy_inode_init(struct inode *inode)
{
	/* Initialize this dummy inode to work as no-op. */
	MSDOS_I(inode)->mmu_private = 0;
	MSDOS_I(inode)->i_start = 0;
	MSDOS_I(inode)->i_logstart = 0;
	MSDOS_I(inode)->i_attrs = 0;
	MSDOS_I(inode)->i_pos = 0;
}