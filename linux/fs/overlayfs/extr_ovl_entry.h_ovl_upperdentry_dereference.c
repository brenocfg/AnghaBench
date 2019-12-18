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
struct ovl_inode {int /*<<< orphan*/  __upperdentry; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct dentry *ovl_upperdentry_dereference(struct ovl_inode *oi)
{
	return READ_ONCE(oi->__upperdentry);
}