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
struct inode {int /*<<< orphan*/  i_lru; TYPE_1__* i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_inode_lru; } ;

/* Variables and functions */
 scalar_t__ list_lru_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_unused ; 
 int /*<<< orphan*/  this_cpu_dec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inode_lru_list_del(struct inode *inode)
{

	if (list_lru_del(&inode->i_sb->s_inode_lru, &inode->i_lru))
		this_cpu_dec(nr_unused);
}