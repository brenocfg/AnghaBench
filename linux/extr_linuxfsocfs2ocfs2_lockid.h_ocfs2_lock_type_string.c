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
typedef  enum ocfs2_lock_type { ____Placeholder_ocfs2_lock_type } ocfs2_lock_type ;

/* Variables and functions */
 char const** ocfs2_lock_type_strings ; 

__attribute__((used)) static inline const char *ocfs2_lock_type_string(enum ocfs2_lock_type type)
{
#ifdef __KERNEL__
	BUG_ON(type >= OCFS2_NUM_LOCK_TYPES);
#endif
	return ocfs2_lock_type_strings[type];
}