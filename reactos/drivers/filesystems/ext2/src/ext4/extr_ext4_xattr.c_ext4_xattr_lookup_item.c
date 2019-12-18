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
struct ext4_xattr_ref {int dummy; } ;
struct ext4_xattr_item {scalar_t__ member_2; char* member_3; size_t member_4; int /*<<< orphan*/  is_data; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 scalar_t__ EXT4_XATTR_INDEX_SYSTEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct ext4_xattr_item* ext4_xattr_item_search (struct ext4_xattr_ref*,struct ext4_xattr_item*) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 

__attribute__((used)) static struct ext4_xattr_item *
ext4_xattr_lookup_item(struct ext4_xattr_ref *xattr_ref, __u8 name_index,
		       const char *name, size_t name_len)
{
	struct ext4_xattr_item tmp = {
		FALSE,
		FALSE,
		name_index,
		(char *)name, /*won't touch this string*/
		name_len,
	};
	if (name_index == EXT4_XATTR_INDEX_SYSTEM &&
	    name_len == 4 &&
	    !memcmp(name, "data", 4))
		tmp.is_data = TRUE;

	return ext4_xattr_item_search(xattr_ref, &tmp);
}