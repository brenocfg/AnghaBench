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
struct qstr {unsigned int len; unsigned char* name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 unsigned int HFS_NAMELEN ; 
 scalar_t__* caseorder ; 

int hfs_compare_dentry(const struct dentry *dentry,
		unsigned int len, const char *str, const struct qstr *name)
{
	const unsigned char *n1, *n2;

	if (len >= HFS_NAMELEN) {
		if (name->len < HFS_NAMELEN)
			return 1;
		len = HFS_NAMELEN;
	} else if (len != name->len)
		return 1;

	n1 = str;
	n2 = name->name;
	while (len--) {
		if (caseorder[*n1++] != caseorder[*n2++])
			return 1;
	}
	return 0;
}