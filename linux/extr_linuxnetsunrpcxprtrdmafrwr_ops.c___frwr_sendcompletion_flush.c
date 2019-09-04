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
struct ib_wc {scalar_t__ status; int /*<<< orphan*/  vendor_err; } ;

/* Variables and functions */
 scalar_t__ IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  ib_wc_status_msg (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__frwr_sendcompletion_flush(struct ib_wc *wc, const char *wr)
{
	if (wc->status != IB_WC_WR_FLUSH_ERR)
		pr_err("rpcrdma: %s: %s (%u/0x%x)\n",
		       wr, ib_wc_status_msg(wc->status),
		       wc->status, wc->vendor_err);
}