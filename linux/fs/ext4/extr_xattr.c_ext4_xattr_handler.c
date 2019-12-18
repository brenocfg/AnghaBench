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
 int ARRAY_SIZE (struct xattr_handler**) ; 
 struct xattr_handler** ext4_xattr_handler_map ; 

__attribute__((used)) static inline const struct xattr_handler *
ext4_xattr_handler(int name_index)
{
	const struct xattr_handler *handler = NULL;

	if (name_index > 0 && name_index < ARRAY_SIZE(ext4_xattr_handler_map))
		handler = ext4_xattr_handler_map[name_index];
	return handler;
}