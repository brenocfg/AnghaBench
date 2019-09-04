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
struct dentry {scalar_t__ d_fsdata; } ;
struct autofs_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct autofs_info *autofs_dentry_ino(struct dentry *dentry)
{
	return (struct autofs_info *)(dentry->d_fsdata);
}