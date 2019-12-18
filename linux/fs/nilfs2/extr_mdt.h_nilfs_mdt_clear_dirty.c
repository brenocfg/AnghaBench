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
struct TYPE_2__ {int /*<<< orphan*/  i_state; } ;

/* Variables and functions */
 TYPE_1__* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  NILFS_I_DIRTY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void nilfs_mdt_clear_dirty(struct inode *inode)
{
	clear_bit(NILFS_I_DIRTY, &NILFS_I(inode)->i_state);
}