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
 int OCFS2_XATTR_MAX ; 
 struct xattr_handler** ocfs2_xattr_handler_map ; 
 char const* xattr_prefix (struct xattr_handler const*) ; 

__attribute__((used)) static inline const char *ocfs2_xattr_prefix(int name_index)
{
	const struct xattr_handler *handler = NULL;

	if (name_index > 0 && name_index < OCFS2_XATTR_MAX)
		handler = ocfs2_xattr_handler_map[name_index];
	return handler ? xattr_prefix(handler) : NULL;
}