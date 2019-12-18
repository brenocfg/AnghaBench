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
struct unicode_map {int /*<<< orphan*/  version; } ;
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct utf8data* utf8nfdi (int /*<<< orphan*/ ) ; 
 scalar_t__ utf8nlen (struct utf8data const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int utf8_validate(const struct unicode_map *um, const struct qstr *str)
{
	const struct utf8data *data = utf8nfdi(um->version);

	if (utf8nlen(data, str->name, str->len) < 0)
		return -1;
	return 0;
}