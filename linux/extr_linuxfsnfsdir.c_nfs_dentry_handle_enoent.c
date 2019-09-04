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
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 scalar_t__ simple_positive (struct dentry*) ; 

__attribute__((used)) static void nfs_dentry_handle_enoent(struct dentry *dentry)
{
	if (simple_positive(dentry))
		d_delete(dentry);
}