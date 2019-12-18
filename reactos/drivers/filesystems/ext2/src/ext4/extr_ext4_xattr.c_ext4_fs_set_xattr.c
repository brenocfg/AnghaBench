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
struct ext4_xattr_item {size_t data_size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int EEXIST ; 
 int ENODATA ; 
 struct ext4_xattr_item* ext4_xattr_insert_item (struct ext4_xattr_ref*,int /*<<< orphan*/ ,char const*,size_t,void const*,size_t,int*) ; 
 struct ext4_xattr_item* ext4_xattr_lookup_item (struct ext4_xattr_ref*,int /*<<< orphan*/ ,char const*,size_t) ; 
 int ext4_xattr_resize_item (struct ext4_xattr_ref*,struct ext4_xattr_item*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 

int ext4_fs_set_xattr(struct ext4_xattr_ref *ref, __u8 name_index,
		      const char *name, size_t name_len, const void *data,
		      size_t data_size, BOOL replace)
{
	int ret = 0;
	struct ext4_xattr_item *item =
	    ext4_xattr_lookup_item(ref, name_index, name, name_len);
	if (replace) {
		if (!item) {
			ret = -ENODATA;
			goto Finish;
		}
		if (item->data_size != data_size)
			ret = ext4_xattr_resize_item(ref, item, data_size);

		if (ret != 0) {
			goto Finish;
		}
		memcpy(item->data, data, data_size);
	} else {
		if (item) {
			ret = -EEXIST;
			goto Finish;
		}
		item = ext4_xattr_insert_item(ref, name_index, name, name_len,
					      data, data_size, &ret);
	}
Finish:
	return ret;
}