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
struct io_kiocb {int flags; } ;

/* Variables and functions */
 int REQ_F_FAIL_LINK ; 
 int REQ_F_LINK ; 
 int /*<<< orphan*/  __io_free_req (struct io_kiocb*) ; 
 int /*<<< orphan*/  io_fail_links (struct io_kiocb*) ; 
 int /*<<< orphan*/  io_req_link_next (struct io_kiocb*) ; 

__attribute__((used)) static void io_free_req(struct io_kiocb *req)
{
	/*
	 * If LINK is set, we have dependent requests in this chain. If we
	 * didn't fail this request, queue the first one up, moving any other
	 * dependencies to the next request. In case of failure, fail the rest
	 * of the chain.
	 */
	if (req->flags & REQ_F_LINK) {
		if (req->flags & REQ_F_FAIL_LINK)
			io_fail_links(req);
		else
			io_req_link_next(req);
	}

	__io_free_req(req);
}