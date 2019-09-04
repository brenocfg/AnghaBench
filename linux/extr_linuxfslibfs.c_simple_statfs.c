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
struct kstatfs {int /*<<< orphan*/  f_namelen; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_MAX ; 
 int /*<<< orphan*/  PAGE_SIZE ; 

int simple_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	buf->f_type = dentry->d_sb->s_magic;
	buf->f_bsize = PAGE_SIZE;
	buf->f_namelen = NAME_MAX;
	return 0;
}