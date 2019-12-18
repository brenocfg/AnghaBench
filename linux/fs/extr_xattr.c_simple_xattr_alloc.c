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
struct simple_xattr {size_t size; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct simple_xattr* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 

struct simple_xattr *simple_xattr_alloc(const void *value, size_t size)
{
	struct simple_xattr *new_xattr;
	size_t len;

	/* wrap around? */
	len = sizeof(*new_xattr) + size;
	if (len < sizeof(*new_xattr))
		return NULL;

	new_xattr = kmalloc(len, GFP_KERNEL);
	if (!new_xattr)
		return NULL;

	new_xattr->size = size;
	memcpy(new_xattr->value, value, size);
	return new_xattr;
}