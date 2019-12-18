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
struct xattr_handler {int dummy; } ;

/* Variables and functions */
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xattr_prefix (struct xattr_handler const*) ; 

const char *xattr_full_name(const struct xattr_handler *handler,
			    const char *name)
{
	size_t prefix_len = strlen(xattr_prefix(handler));

	return name - prefix_len;
}