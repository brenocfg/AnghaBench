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
struct xdomain_request_work {int /*<<< orphan*/  work; struct tb* tb; int /*<<< orphan*/  pkg; } ;
struct tb_xdp_header {int dummy; } ;
struct tb {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xdomain_request_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemdup (struct tb_xdp_header const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_xdp_handle_request ; 

__attribute__((used)) static void
tb_xdp_schedule_request(struct tb *tb, const struct tb_xdp_header *hdr,
			size_t size)
{
	struct xdomain_request_work *xw;

	xw = kmalloc(sizeof(*xw), GFP_KERNEL);
	if (!xw)
		return;

	INIT_WORK(&xw->work, tb_xdp_handle_request);
	xw->pkg = kmemdup(hdr, size, GFP_KERNEL);
	xw->tb = tb;

	queue_work(tb->wq, &xw->work);
}