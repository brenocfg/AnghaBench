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

/* Variables and functions */
 int ENODATA ; 
 struct ext4_xattr_item* ext4_xattr_lookup_item (struct ext4_xattr_ref*,int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 

int ext4_fs_get_xattr(struct ext4_xattr_ref *ref, __u8 name_index,
		      const char *name, size_t name_len, void *buf,
		      size_t buf_size, size_t *data_size)
{
	int ret = 0;
	size_t item_size = 0;
	struct ext4_xattr_item *item =
	    ext4_xattr_lookup_item(ref, name_index, name, name_len);

	if (!item) {
		ret = -ENODATA;
		goto Finish;
	}
	item_size = item->data_size;
	if (buf_size > item_size)
		buf_size = item_size;

	if (buf)
		memcpy(buf, item->data, buf_size);

Finish:
	if (data_size)
		*data_size = item_size;

	return ret;
}