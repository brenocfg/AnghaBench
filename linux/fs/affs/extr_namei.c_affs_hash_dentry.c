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
struct qstr {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int __affs_hash_dentry (struct dentry const*,struct qstr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_nofilenametruncate (struct dentry const*) ; 
 int /*<<< orphan*/  affs_toupper ; 

__attribute__((used)) static int
affs_hash_dentry(const struct dentry *dentry, struct qstr *qstr)
{
	return __affs_hash_dentry(dentry, qstr, affs_toupper,
				  affs_nofilenametruncate(dentry));

}