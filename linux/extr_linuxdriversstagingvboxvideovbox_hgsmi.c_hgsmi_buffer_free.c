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
typedef  int /*<<< orphan*/  u8 ;
struct hgsmi_buffer_tail {int dummy; } ;
struct hgsmi_buffer_header {int data_size; } ;
struct gen_pool {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_free (struct gen_pool*,unsigned long,size_t) ; 

void hgsmi_buffer_free(struct gen_pool *guest_pool, void *buf)
{
	struct hgsmi_buffer_header *h =
		(struct hgsmi_buffer_header *)((u8 *)buf - sizeof(*h));
	size_t total_size = h->data_size + sizeof(*h) +
					     sizeof(struct hgsmi_buffer_tail);

	gen_pool_free(guest_pool, (unsigned long)h, total_size);
}