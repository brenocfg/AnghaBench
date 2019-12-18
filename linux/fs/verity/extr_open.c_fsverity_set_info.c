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
struct inode {int /*<<< orphan*/  i_verity_info; } ;
struct fsverity_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct fsverity_info*) ; 
 int /*<<< orphan*/  fsverity_free_info (struct fsverity_info*) ; 

void fsverity_set_info(struct inode *inode, struct fsverity_info *vi)
{
	/*
	 * Multiple processes may race to set ->i_verity_info, so use cmpxchg.
	 * This pairs with the READ_ONCE() in fsverity_get_info().
	 */
	if (cmpxchg(&inode->i_verity_info, NULL, vi) != NULL)
		fsverity_free_info(vi);
}