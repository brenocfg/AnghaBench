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
struct qstr {unsigned int len; char* name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
adfs_compare(const struct dentry *dentry,
		unsigned int len, const char *str, const struct qstr *name)
{
	int i;

	if (len != name->len)
		return 1;

	for (i = 0; i < name->len; i++) {
		char a, b;

		a = str[i];
		b = name->name[i];

		if (a >= 'A' && a <= 'Z')
			a += 'a' - 'A';
		if (b >= 'A' && b <= 'Z')
			b += 'a' - 'A';

		if (a != b)
			return 1;
	}
	return 0;
}