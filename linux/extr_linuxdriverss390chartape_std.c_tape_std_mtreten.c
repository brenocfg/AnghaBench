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
struct tape_request {scalar_t__ cpaddr; int /*<<< orphan*/  op; } ;
struct tape_device {int /*<<< orphan*/ * modeset_byte; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_TIC ; 
 int /*<<< orphan*/  FORSPACEFILE ; 
 scalar_t__ IS_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  MODE_SET_DB ; 
 int /*<<< orphan*/  MTREW ; 
 int /*<<< orphan*/  NOP ; 
 int PTR_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  TO_FSF ; 
 struct tape_request* tape_alloc_request (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_ccw_cc (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tape_ccw_end (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tape_do_io_interruptible (struct tape_device*,struct tape_request*) ; 
 int /*<<< orphan*/  tape_free_request (struct tape_request*) ; 
 int tape_mtop (struct tape_device*,int /*<<< orphan*/ ,int) ; 

int
tape_std_mtreten(struct tape_device *device, int mt_count)
{
	struct tape_request *request;

	request = tape_alloc_request(4, 0);
	if (IS_ERR(request))
		return PTR_ERR(request);
	request->op = TO_FSF;
	/* setup ccws */
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_cc(request->cpaddr + 1,FORSPACEFILE, 0, NULL);
	tape_ccw_cc(request->cpaddr + 2, NOP, 0, NULL);
	tape_ccw_end(request->cpaddr + 3, CCW_CMD_TIC, 0, request->cpaddr);
	/* execute it, MTRETEN rc gets ignored */
	tape_do_io_interruptible(device, request);
	tape_free_request(request);
	return tape_mtop(device, MTREW, 1);
}