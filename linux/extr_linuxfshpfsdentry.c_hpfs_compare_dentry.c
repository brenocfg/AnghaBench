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
struct qstr {unsigned int len; int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpfs_adjust_length (char const*,unsigned int*) ; 
 scalar_t__ hpfs_chk_name (int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ hpfs_compare_names (int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpfs_compare_dentry(const struct dentry *dentry,
		unsigned int len, const char *str, const struct qstr *name)
{
	unsigned al = len;
	unsigned bl = name->len;

	hpfs_adjust_length(str, &al);
	/*hpfs_adjust_length(b->name, &bl);*/

	/*
	 * 'str' is the nane of an already existing dentry, so the name
	 * must be valid. 'name' must be validated first.
	 */

	if (hpfs_chk_name(name->name, &bl))
		return 1;
	if (hpfs_compare_names(dentry->d_sb, str, al, name->name, bl, 0))
		return 1;
	return 0;
}