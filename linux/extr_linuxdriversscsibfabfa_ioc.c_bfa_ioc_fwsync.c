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
typedef  scalar_t__ u32 ;
struct bfa_ioc_s {int dummy; } ;

/* Variables and functions */
 scalar_t__ bfa_ioc_mbox_cmd_pending (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_send_fwsync (struct bfa_ioc_s*) ; 

__attribute__((used)) static void
bfa_ioc_fwsync(struct bfa_ioc_s *ioc)
{
	u32 fwsync_iter = 1000;

	bfa_ioc_send_fwsync(ioc);

	/*
	 * After sending a fw sync mbox command wait for it to
	 * take effect.  We will not wait for a response because
	 *    1. fw_sync mbox cmd doesn't have a response.
	 *    2. Even if we implement that,  interrupts might not
	 *	 be enabled when we call this function.
	 * So, just keep checking if any mbox cmd is pending, and
	 * after waiting for a reasonable amount of time, go ahead.
	 * It is possible that fw has crashed and the mbox command
	 * is never acknowledged.
	 */
	while (bfa_ioc_mbox_cmd_pending(ioc) && fwsync_iter > 0)
		fwsync_iter--;
}