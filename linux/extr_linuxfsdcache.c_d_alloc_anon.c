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
struct super_block {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* __d_alloc (struct super_block*,int /*<<< orphan*/ *) ; 

struct dentry *d_alloc_anon(struct super_block *sb)
{
	return __d_alloc(sb, NULL);
}