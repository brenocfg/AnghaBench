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
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  NO_CHECK_TYPE ; 
 int __get_data_block (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_data_block(struct inode *inode, sector_t iblock,
			struct buffer_head *bh_result, int create, int flag,
			pgoff_t *next_pgofs)
{
	return __get_data_block(inode, iblock, bh_result, create,
							flag, next_pgofs,
							NO_CHECK_TYPE, create);
}