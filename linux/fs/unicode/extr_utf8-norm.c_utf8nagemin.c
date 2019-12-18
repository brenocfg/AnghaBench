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
typedef  int /*<<< orphan*/  utf8leaf_t ;
struct utf8data {int maxage; } ;

/* Variables and functions */
 size_t LEAF_GEN (int /*<<< orphan*/ *) ; 
 int UTF8HANGULLEAF ; 
 int* utf8agetab ; 
 scalar_t__ utf8clen (char const*) ; 
 int /*<<< orphan*/ * utf8nlookup (struct utf8data const*,unsigned char*,char const*,size_t) ; 

int utf8nagemin(const struct utf8data *data, const char *s, size_t len)
{
	utf8leaf_t	*leaf;
	int		leaf_age;
	int		age;
	unsigned char	hangul[UTF8HANGULLEAF];

	if (!data)
		return -1;
	age = data->maxage;
	while (len && *s) {
		leaf = utf8nlookup(data, hangul, s, len);
		if (!leaf)
			return -1;
		leaf_age = utf8agetab[LEAF_GEN(leaf)];
		if (leaf_age <= data->maxage && leaf_age < age)
			age = leaf_age;
		len -= utf8clen(s);
		s += utf8clen(s);
	}
	return age;
}