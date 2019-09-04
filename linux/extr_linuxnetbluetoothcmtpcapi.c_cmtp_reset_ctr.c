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
struct cmtp_session {int /*<<< orphan*/  task; int /*<<< orphan*/  terminate; } ;
struct capi_ctr {struct cmtp_session* driverdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct capi_ctr*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capi_ctr_down (struct capi_ctr*) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmtp_reset_ctr(struct capi_ctr *ctrl)
{
	struct cmtp_session *session = ctrl->driverdata;

	BT_DBG("ctrl %p", ctrl);

	capi_ctr_down(ctrl);

	atomic_inc(&session->terminate);
	wake_up_process(session->task);
}