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
typedef  int /*<<< orphan*/  u32 ;
struct io_uring_sqe {int dummy; } ;
struct io_uring_params {scalar_t__ sq_entries; scalar_t__ cq_entries; } ;
struct io_rings {scalar_t__ cq_ring_entries; scalar_t__ sq_ring_entries; scalar_t__ cq_ring_mask; scalar_t__ sq_ring_mask; } ;
struct io_ring_ctx {void* sq_sqes; scalar_t__ cq_entries; scalar_t__ sq_entries; scalar_t__ cq_mask; scalar_t__ sq_mask; int /*<<< orphan*/ * sq_array; struct io_rings* rings; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOVERFLOW ; 
 size_t SIZE_MAX ; 
 size_t array_size (int,scalar_t__) ; 
 void* io_mem_alloc (size_t) ; 
 size_t rings_size (scalar_t__,scalar_t__,size_t*) ; 

__attribute__((used)) static int io_allocate_scq_urings(struct io_ring_ctx *ctx,
				  struct io_uring_params *p)
{
	struct io_rings *rings;
	size_t size, sq_array_offset;

	size = rings_size(p->sq_entries, p->cq_entries, &sq_array_offset);
	if (size == SIZE_MAX)
		return -EOVERFLOW;

	rings = io_mem_alloc(size);
	if (!rings)
		return -ENOMEM;

	ctx->rings = rings;
	ctx->sq_array = (u32 *)((char *)rings + sq_array_offset);
	rings->sq_ring_mask = p->sq_entries - 1;
	rings->cq_ring_mask = p->cq_entries - 1;
	rings->sq_ring_entries = p->sq_entries;
	rings->cq_ring_entries = p->cq_entries;
	ctx->sq_mask = rings->sq_ring_mask;
	ctx->cq_mask = rings->cq_ring_mask;
	ctx->sq_entries = rings->sq_ring_entries;
	ctx->cq_entries = rings->cq_ring_entries;

	size = array_size(sizeof(struct io_uring_sqe), p->sq_entries);
	if (size == SIZE_MAX)
		return -EOVERFLOW;

	ctx->sq_sqes = io_mem_alloc(size);
	if (!ctx->sq_sqes)
		return -ENOMEM;

	return 0;
}