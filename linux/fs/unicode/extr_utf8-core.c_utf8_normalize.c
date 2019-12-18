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
typedef  size_t ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int utf8byte (struct utf8cursor*) ; 
 scalar_t__ utf8ncursor (struct utf8cursor*,struct utf8data const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct utf8data* utf8nfdi (int /*<<< orphan*/ ) ; 

int utf8_normalize(const struct unicode_map *um, const struct qstr *str,
		   unsigned char *dest, size_t dlen)
{
	const struct utf8data *data = utf8nfdi(um->version);
	struct utf8cursor cur;
	ssize_t nlen = 0;

	if (utf8ncursor(&cur, data, str->name, str->len) < 0)
		return -EINVAL;

	for (nlen = 0; nlen < dlen; nlen++) {
		int c = utf8byte(&cur);

		dest[nlen] = c;
		if (!c)
			return nlen;
		if (c == -1)
			break;
	}
	return -EINVAL;
}