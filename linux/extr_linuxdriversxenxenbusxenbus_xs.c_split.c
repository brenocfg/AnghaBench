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

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 char** ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_NOIO ; 
 int __GFP_HIGH ; 
 unsigned int count_strings (char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char** kmalloc (unsigned int,int) ; 
 int /*<<< orphan*/  memcpy (char**,char*,unsigned int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char **split(char *strings, unsigned int len, unsigned int *num)
{
	char *p, **ret;

	/* Count the strings. */
	*num = count_strings(strings, len);

	/* Transfer to one big alloc for easy freeing. */
	ret = kmalloc(*num * sizeof(char *) + len, GFP_NOIO | __GFP_HIGH);
	if (!ret) {
		kfree(strings);
		return ERR_PTR(-ENOMEM);
	}
	memcpy(&ret[*num], strings, len);
	kfree(strings);

	strings = (char *)&ret[*num];
	for (p = strings, *num = 0; p < strings + len; p += strlen(p) + 1)
		ret[(*num)++] = p;

	return ret;
}