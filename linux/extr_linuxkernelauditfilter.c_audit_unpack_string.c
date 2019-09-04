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
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PATH_MAX ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,void*,size_t) ; 
 scalar_t__ unlikely (int) ; 

char *audit_unpack_string(void **bufp, size_t *remain, size_t len)
{
	char *str;

	if (!*bufp || (len == 0) || (len > *remain))
		return ERR_PTR(-EINVAL);

	/* Of the currently implemented string fields, PATH_MAX
	 * defines the longest valid length.
	 */
	if (len > PATH_MAX)
		return ERR_PTR(-ENAMETOOLONG);

	str = kmalloc(len + 1, GFP_KERNEL);
	if (unlikely(!str))
		return ERR_PTR(-ENOMEM);

	memcpy(str, *bufp, len);
	str[len] = 0;
	*bufp += len;
	*remain -= len;

	return str;
}