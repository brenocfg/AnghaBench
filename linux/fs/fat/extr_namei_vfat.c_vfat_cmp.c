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
struct qstr {int /*<<< orphan*/  name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 unsigned int __vfat_striptail_len (unsigned int,char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,unsigned int) ; 
 unsigned int vfat_striptail_len (struct qstr const*) ; 

__attribute__((used)) static int vfat_cmp(const struct dentry *dentry,
		unsigned int len, const char *str, const struct qstr *name)
{
	unsigned int alen, blen;

	/* A filename cannot end in '.' or we treat it like it has none */
	alen = vfat_striptail_len(name);
	blen = __vfat_striptail_len(len, str);
	if (alen == blen) {
		if (strncmp(name->name, str, alen) == 0)
			return 0;
	}
	return 1;
}