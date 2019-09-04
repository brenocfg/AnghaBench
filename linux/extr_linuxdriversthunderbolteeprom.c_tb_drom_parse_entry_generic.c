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
struct tb_switch {void* device_name; void* vendor_name; } ;
struct tb_drom_entry_header {int index; int /*<<< orphan*/  len; } ;
struct tb_drom_entry_generic {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kstrndup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tb_drom_parse_entry_generic(struct tb_switch *sw,
		struct tb_drom_entry_header *header)
{
	const struct tb_drom_entry_generic *entry =
		(const struct tb_drom_entry_generic *)header;

	switch (header->index) {
	case 1:
		/* Length includes 2 bytes header so remove it before copy */
		sw->vendor_name = kstrndup(entry->data,
			header->len - sizeof(*header), GFP_KERNEL);
		if (!sw->vendor_name)
			return -ENOMEM;
		break;

	case 2:
		sw->device_name = kstrndup(entry->data,
			header->len - sizeof(*header), GFP_KERNEL);
		if (!sw->device_name)
			return -ENOMEM;
		break;
	}

	return 0;
}