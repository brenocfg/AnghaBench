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
struct ext2_xattr_entry {int e_name_index; size_t e_name_len; int /*<<< orphan*/  e_name; } ;

/* Variables and functions */
 int memcmp (char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
ext2_xattr_cmp_entry(int name_index, size_t name_len, const char *name,
		     struct ext2_xattr_entry *entry)
{
	int cmp;

	cmp = name_index - entry->e_name_index;
	if (!cmp)
		cmp = name_len - entry->e_name_len;
	if (!cmp)
		cmp = memcmp(name, entry->e_name, name_len);

	return cmp;
}