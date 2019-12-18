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
 int __affs_compare_dentry (unsigned int,char const*,struct qstr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_intl_toupper ; 
 int /*<<< orphan*/  affs_nofilenametruncate (struct dentry const*) ; 

__attribute__((used)) static int
affs_intl_compare_dentry(const struct dentry *dentry,
		unsigned int len, const char *str, const struct qstr *name)
{
	return __affs_compare_dentry(len, str, name, affs_intl_toupper,
				     affs_nofilenametruncate(dentry));

}