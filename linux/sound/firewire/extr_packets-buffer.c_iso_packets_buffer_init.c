#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * pages; } ;
struct iso_packets_buffer {TYPE_1__* packets; TYPE_4__ iso_buffer; } ;
struct fw_unit {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_6__ {int /*<<< orphan*/  card; } ;
struct TYPE_5__ {unsigned int offset; void* buffer; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int L1_CACHE_ALIGN (unsigned int) ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 int fw_iso_buffer_init (TYPE_4__*,int /*<<< orphan*/ ,unsigned int,int) ; 
 TYPE_3__* fw_parent_device (struct fw_unit*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 void* page_address (int /*<<< orphan*/ ) ; 

int iso_packets_buffer_init(struct iso_packets_buffer *b, struct fw_unit *unit,
			    unsigned int count, unsigned int packet_size,
			    enum dma_data_direction direction)
{
	unsigned int packets_per_page, pages;
	unsigned int i, page_index, offset_in_page;
	void *p;
	int err;

	b->packets = kmalloc_array(count, sizeof(*b->packets), GFP_KERNEL);
	if (!b->packets) {
		err = -ENOMEM;
		goto error;
	}

	packet_size = L1_CACHE_ALIGN(packet_size);
	packets_per_page = PAGE_SIZE / packet_size;
	if (WARN_ON(!packets_per_page)) {
		err = -EINVAL;
		goto err_packets;
	}
	pages = DIV_ROUND_UP(count, packets_per_page);

	err = fw_iso_buffer_init(&b->iso_buffer, fw_parent_device(unit)->card,
				 pages, direction);
	if (err < 0)
		goto err_packets;

	for (i = 0; i < count; ++i) {
		page_index = i / packets_per_page;
		p = page_address(b->iso_buffer.pages[page_index]);
		offset_in_page = (i % packets_per_page) * packet_size;
		b->packets[i].buffer = p + offset_in_page;
		b->packets[i].offset = page_index * PAGE_SIZE + offset_in_page;
	}

	return 0;

err_packets:
	kfree(b->packets);
error:
	return err;
}