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
struct qstr {int len; char* name; } ;
struct object_info {int name_len; char* name; } ;

/* Variables and functions */

__attribute__((used)) static int
adfs_match(const struct qstr *name, struct object_info *obj)
{
	int i;

	if (name->len != obj->name_len)
		return 0;

	for (i = 0; i < name->len; i++) {
		char c1, c2;

		c1 = name->name[i];
		c2 = obj->name[i];

		if (c1 >= 'A' && c1 <= 'Z')
			c1 += 'a' - 'A';
		if (c2 >= 'A' && c2 <= 'Z')
			c2 += 'a' - 'A';

		if (c1 != c2)
			return 0;
	}
	return 1;
}