#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct z3fold_pool {TYPE_3__* inode; } ;
struct TYPE_7__ {TYPE_1__* i_mapping; } ;
struct TYPE_6__ {int /*<<< orphan*/  mnt_sb; } ;
struct TYPE_5__ {int /*<<< orphan*/ * a_ops; struct z3fold_pool* private_data; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_3__*) ; 
 TYPE_3__* alloc_anon_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  z3fold_aops ; 
 TYPE_2__* z3fold_mnt ; 

__attribute__((used)) static int z3fold_register_migration(struct z3fold_pool *pool)
{
	pool->inode = alloc_anon_inode(z3fold_mnt->mnt_sb);
	if (IS_ERR(pool->inode)) {
		pool->inode = NULL;
		return 1;
	}

	pool->inode->i_mapping->private_data = pool;
	pool->inode->i_mapping->a_ops = &z3fold_aops;
	return 0;
}