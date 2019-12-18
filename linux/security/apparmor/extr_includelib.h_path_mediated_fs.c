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
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {int s_flags; } ;

/* Variables and functions */
 int SB_NOUSER ; 

__attribute__((used)) static inline bool path_mediated_fs(struct dentry *dentry)
{
	return !(dentry->d_sb->s_flags & SB_NOUSER);
}