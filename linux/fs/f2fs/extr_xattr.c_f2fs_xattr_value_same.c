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
struct f2fs_xattr_entry {int e_name_len; int /*<<< orphan*/  e_value_size; void* e_name; } ;

/* Variables and functions */
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (void*,void const*,size_t) ; 

__attribute__((used)) static bool f2fs_xattr_value_same(struct f2fs_xattr_entry *entry,
					const void *value, size_t size)
{
	void *pval = entry->e_name + entry->e_name_len;

	return (le16_to_cpu(entry->e_value_size) == size) &&
					!memcmp(pval, value, size);
}