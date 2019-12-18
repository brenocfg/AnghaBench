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
struct utf8data {int dummy; } ;
struct utf8cursor {int dummy; } ;
struct unicode_map {int /*<<< orphan*/  version; } ;
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int utf8byte (struct utf8cursor*) ; 
 scalar_t__ utf8ncursor (struct utf8cursor*,struct utf8data const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct utf8data* utf8nfdicf (int /*<<< orphan*/ ) ; 

int utf8_strncasecmp(const struct unicode_map *um,
		     const struct qstr *s1, const struct qstr *s2)
{
	const struct utf8data *data = utf8nfdicf(um->version);
	struct utf8cursor cur1, cur2;
	int c1, c2;

	if (utf8ncursor(&cur1, data, s1->name, s1->len) < 0)
		return -EINVAL;

	if (utf8ncursor(&cur2, data, s2->name, s2->len) < 0)
		return -EINVAL;

	do {
		c1 = utf8byte(&cur1);
		c2 = utf8byte(&cur2);

		if (c1 < 0 || c2 < 0)
			return -EINVAL;
		if (c1 != c2)
			return 1;
	} while (c1);

	return 0;
}