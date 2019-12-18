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
 int /*<<< orphan*/  utf8clen (char const*) ; 
 int /*<<< orphan*/ * utf8lookup (struct tree*,unsigned char*,char const*) ; 

int utf8agemax(struct tree *tree, const char *s)
{
	utf8leaf_t	*leaf;
	int		age = 0;
	int		leaf_age;
	unsigned char	hangul[UTF8HANGULLEAF];

	if (!tree)
		return -1;

	while (*s) {
		leaf = utf8lookup(tree, hangul, s);
		if (!leaf)
			return -1;
		leaf_age = ages[LEAF_GEN(leaf)];
		if (leaf_age <= tree->maxage && leaf_age > age)
			age = leaf_age;
		s += utf8clen(s);
	}
	return age;
}