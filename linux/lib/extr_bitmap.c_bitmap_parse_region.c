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
struct region {scalar_t__ end; scalar_t__ group_len; scalar_t__ off; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (char const*) ; 
 char const* bitmap_getnum (char const*,scalar_t__*) ; 
 scalar_t__ end_of_region (char const) ; 
 scalar_t__ end_of_str (char const) ; 

__attribute__((used)) static const char *bitmap_parse_region(const char *str, struct region *r)
{
	str = bitmap_getnum(str, &r->start);
	if (IS_ERR(str))
		return str;

	if (end_of_region(*str))
		goto no_end;

	if (*str != '-')
		return ERR_PTR(-EINVAL);

	str = bitmap_getnum(str + 1, &r->end);
	if (IS_ERR(str))
		return str;

	if (end_of_region(*str))
		goto no_pattern;

	if (*str != ':')
		return ERR_PTR(-EINVAL);

	str = bitmap_getnum(str + 1, &r->off);
	if (IS_ERR(str))
		return str;

	if (*str != '/')
		return ERR_PTR(-EINVAL);

	return bitmap_getnum(str + 1, &r->group_len);

no_end:
	r->end = r->start;
no_pattern:
	r->off = r->end + 1;
	r->group_len = r->end + 1;

	return end_of_str(*str) ? NULL : str;
}