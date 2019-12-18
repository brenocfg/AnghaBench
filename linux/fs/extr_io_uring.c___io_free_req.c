#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct io_kiocb {int flags; TYPE_1__* ctx; scalar_t__ file; } ;
struct TYPE_2__ {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int REQ_F_FIXED_FILE ; 
 int /*<<< orphan*/  fput (scalar_t__) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct io_kiocb*) ; 
 int /*<<< orphan*/  percpu_ref_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  req_cachep ; 

__attribute__((used)) static void __io_free_req(struct io_kiocb *req)
{
	if (req->file && !(req->flags & REQ_F_FIXED_FILE))
		fput(req->file);
	percpu_ref_put(&req->ctx->refs);
	kmem_cache_free(req_cachep, req);
}