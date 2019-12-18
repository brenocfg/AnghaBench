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
struct TYPE_2__ {int /*<<< orphan*/ * mi_palloc_cache; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  nilfs_palloc_clear_cache (struct inode*) ; 

void nilfs_palloc_destroy_cache(struct inode *inode)
{
	nilfs_palloc_clear_cache(inode);
	NILFS_MDT(inode)->mi_palloc_cache = NULL;
}