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
struct qe_udc {scalar_t__ ep0_dir; int /*<<< orphan*/  ep0_state; int /*<<< orphan*/ * eps; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAIT_FOR_SETUP ; 
 int /*<<< orphan*/  qe_eprx_stall_change (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qe_eptx_stall_change (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int qe_ep0_stall(struct qe_udc *udc)
{
	qe_eptx_stall_change(&udc->eps[0], 1);
	qe_eprx_stall_change(&udc->eps[0], 1);
	udc->ep0_state = WAIT_FOR_SETUP;
	udc->ep0_dir = 0;
	return 0;
}