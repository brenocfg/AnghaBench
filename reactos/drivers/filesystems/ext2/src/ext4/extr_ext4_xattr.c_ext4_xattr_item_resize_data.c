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
struct ext4_xattr_item {size_t data_size; void* data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

__attribute__((used)) static int ext4_xattr_item_resize_data(struct ext4_xattr_item *item,
				       size_t new_data_size)
{
	if (new_data_size != item->data_size) {
		void *new_data;
		new_data = kmalloc(new_data_size, GFP_NOFS);
		if (!new_data)
			return -ENOMEM;

		memcpy(new_data, item->data, item->data_size);
		kfree(item->data);

		item->data = new_data;
		item->data_size = new_data_size;
	}
	return 0;
}