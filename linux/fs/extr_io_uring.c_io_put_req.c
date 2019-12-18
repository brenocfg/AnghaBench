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
struct io_kiocb {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  io_free_req (struct io_kiocb*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void io_put_req(struct io_kiocb *req)
{
	if (refcount_dec_and_test(&req->refs))
		io_free_req(req);
}