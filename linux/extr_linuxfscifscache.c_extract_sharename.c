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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kstrndup (char*,int,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 int strlen (char*) ; 

char *extract_sharename(const char *treename)
{
	const char *src;
	char *delim, *dst;
	int len;

	/* skip double chars at the beginning */
	src = treename + 2;

	/* share name is always preceded by '\\' now */
	delim = strchr(src, '\\');
	if (!delim)
		return ERR_PTR(-EINVAL);
	delim++;
	len = strlen(delim);

	/* caller has to free the memory */
	dst = kstrndup(delim, len, GFP_KERNEL);
	if (!dst)
		return ERR_PTR(-ENOMEM);

	return dst;
}