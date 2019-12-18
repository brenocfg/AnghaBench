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
struct erofs_xattr_entry {int /*<<< orphan*/  e_value_size; scalar_t__ e_name_len; } ;

/* Variables and functions */
 unsigned int EROFS_XATTR_ALIGN (scalar_t__) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int erofs_xattr_entry_size(struct erofs_xattr_entry *e)
{
	return EROFS_XATTR_ALIGN(sizeof(struct erofs_xattr_entry) +
				 e->e_name_len + le16_to_cpu(e->e_value_size));
}