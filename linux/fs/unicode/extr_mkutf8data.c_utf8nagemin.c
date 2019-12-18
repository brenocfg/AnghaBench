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
struct tree {int maxage; } ;

/* Variables and functions */
 size_t LEAF_GEN (int /*<<< orphan*/ *) ; 
 int UTF8HANGULLEAF ; 
 int* ages ; 
 scalar_t__ utf8clen (char const*) ; 
 int /*<<< orphan*/ * utf8nlookup (struct tree*,unsigned char*,char const*,size_t) ; 

int utf8nagemin(struct tree *tree, const char *s, size_t len)
{
	utf8leaf_t	*leaf;
	int		leaf_age;
	int		age;
	unsigned char	hangul[UTF8HANGULLEAF];

	if (!tree)
		return -1;
	age = tree->maxage;
        while (len && *s) {
		leaf = utf8nlookup(tree, hangul, s, len);
		if (!leaf)
			return -1;
		leaf_age = ages[LEAF_GEN(leaf)];
		if (leaf_age <= tree->maxage && leaf_age < age)
			age = leaf_age;
		len -= utf8clen(s);
		s += utf8clen(s);
	}
	return age;
}