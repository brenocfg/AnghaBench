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
struct the_nilfs {unsigned long ns_nsegments; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {scalar_t__ s_fs_info; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long nilfs_sufile_get_nsegments(struct inode *sufile)
{
	return ((struct the_nilfs *)sufile->i_sb->s_fs_info)->ns_nsegments;
}