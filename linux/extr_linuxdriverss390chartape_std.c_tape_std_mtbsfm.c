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
struct tape_request {int /*<<< orphan*/  cpaddr; int /*<<< orphan*/  op; } ;
struct tape_device {int /*<<< orphan*/  modeset_byte; } ;
struct ccw1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKSPACEFILE ; 
 scalar_t__ IS_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  MODE_SET_DB ; 
 int /*<<< orphan*/  NOP ; 
 int PTR_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  TO_BSF ; 
 struct tape_request* tape_alloc_request (int,int /*<<< orphan*/ ) ; 
 struct ccw1* tape_ccw_cc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ccw1* tape_ccw_end (struct ccw1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ccw1* tape_ccw_repeat (struct ccw1*,int /*<<< orphan*/ ,int) ; 
 int tape_do_io_free (struct tape_device*,struct tape_request*) ; 

int
tape_std_mtbsfm(struct tape_device *device, int mt_count)
{
	struct tape_request *request;
	struct ccw1 *ccw;

	request = tape_alloc_request(mt_count + 2, 0);
	if (IS_ERR(request))
		return PTR_ERR(request);
	request->op = TO_BSF;
	/* setup ccws */
	ccw = tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1,
			  device->modeset_byte);
	ccw = tape_ccw_repeat(ccw, BACKSPACEFILE, mt_count);
	ccw = tape_ccw_end(ccw, NOP, 0, NULL);

	/* execute it */
	return tape_do_io_free(device, request);
}