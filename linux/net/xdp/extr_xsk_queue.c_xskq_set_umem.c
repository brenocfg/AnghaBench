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
typedef  void* u64 ;
struct xsk_queue {void* chunk_mask; void* size; } ;

/* Variables and functions */

void xskq_set_umem(struct xsk_queue *q, u64 size, u64 chunk_mask)
{
	if (!q)
		return;

	q->size = size;
	q->chunk_mask = chunk_mask;
}