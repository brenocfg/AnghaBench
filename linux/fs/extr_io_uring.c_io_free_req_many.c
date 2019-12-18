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
struct io_ring_ctx {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free_bulk (int /*<<< orphan*/ ,int,void**) ; 
 int /*<<< orphan*/  percpu_ref_put_many (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  req_cachep ; 

__attribute__((used)) static void io_free_req_many(struct io_ring_ctx *ctx, void **reqs, int *nr)
{
	if (*nr) {
		kmem_cache_free_bulk(req_cachep, *nr, reqs);
		percpu_ref_put_many(&ctx->refs, *nr);
		*nr = 0;
	}
}