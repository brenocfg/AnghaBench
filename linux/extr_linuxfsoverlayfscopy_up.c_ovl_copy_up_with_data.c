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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_WRONLY ; 
 int ovl_copy_up_flags (struct dentry*,int /*<<< orphan*/ ) ; 

int ovl_copy_up_with_data(struct dentry *dentry)
{
	return ovl_copy_up_flags(dentry, O_WRONLY);
}