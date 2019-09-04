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
struct sk_msg_buff {int sg_start; scalar_t__ data; scalar_t__ data_end; scalar_t__* sg_copy; struct scatterlist* sg_data; } ;
struct scatterlist {scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ sg_virt (struct scatterlist*) ; 

__attribute__((used)) static inline void bpf_compute_data_pointers_sg(struct sk_msg_buff *md)
{
	struct scatterlist *sg = md->sg_data + md->sg_start;

	if (md->sg_copy[md->sg_start]) {
		md->data = md->data_end = 0;
	} else {
		md->data = sg_virt(sg);
		md->data_end = md->data + sg->length;
	}
}