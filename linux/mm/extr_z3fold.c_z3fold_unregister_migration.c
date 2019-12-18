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
struct z3fold_pool {scalar_t__ inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  iput (scalar_t__) ; 

__attribute__((used)) static void z3fold_unregister_migration(struct z3fold_pool *pool)
{
	if (pool->inode)
		iput(pool->inode);
 }