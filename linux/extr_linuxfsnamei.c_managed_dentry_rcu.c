#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_2__* dentry; } ;
struct TYPE_4__ {int d_flags; TYPE_1__* d_op; } ;
struct TYPE_3__ {int (* d_manage ) (struct path const*,int) ;} ;

/* Variables and functions */
 int DCACHE_MANAGE_TRANSIT ; 
 int stub1 (struct path const*,int) ; 

__attribute__((used)) static inline int managed_dentry_rcu(const struct path *path)
{
	return (path->dentry->d_flags & DCACHE_MANAGE_TRANSIT) ?
		path->dentry->d_op->d_manage(path, true) : 0;
}