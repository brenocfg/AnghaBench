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
struct io_ring_ctx {int dummy; } ;
struct io_kiocb {int flags; } ;

/* Variables and functions */
 int REQ_F_IO_DRAIN ; 
 int REQ_F_IO_DRAINED ; 
 int __io_sequence_defer (struct io_ring_ctx*,struct io_kiocb*) ; 

__attribute__((used)) static inline bool io_sequence_defer(struct io_ring_ctx *ctx,
				     struct io_kiocb *req)
{
	if ((req->flags & (REQ_F_IO_DRAIN|REQ_F_IO_DRAINED)) != REQ_F_IO_DRAIN)
		return false;

	return __io_sequence_defer(ctx, req);
}