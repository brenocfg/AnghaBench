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
struct dentry {void* d_fsdata; TYPE_1__* d_sb; } ;
struct TYPE_2__ {scalar_t__ s_magic; } ;

/* Variables and functions */
 scalar_t__ DEVPTS_SUPER_MAGIC ; 

void *devpts_get_priv(struct dentry *dentry)
{
	if (dentry->d_sb->s_magic != DEVPTS_SUPER_MAGIC)
		return NULL;
	return dentry->d_fsdata;
}