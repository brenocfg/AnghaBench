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
struct dentry {int dummy; } ;
struct TYPE_2__ {int c_flags; } ;

/* Variables and functions */
 int C_PURGE ; 
 TYPE_1__* ITOC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry const*) ; 
 scalar_t__ d_really_is_negative (struct dentry const*) ; 
 scalar_t__ is_bad_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int coda_dentry_delete(const struct dentry * dentry)
{
	int flags;

	if (d_really_is_negative(dentry)) 
		return 0;

	flags = (ITOC(d_inode(dentry))->c_flags) & C_PURGE;
	if (is_bad_inode(d_inode(dentry)) || flags) {
		return 1;
	}
	return 0;
}