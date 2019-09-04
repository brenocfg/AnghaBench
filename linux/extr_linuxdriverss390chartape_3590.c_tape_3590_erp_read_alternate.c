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
struct tape_request {int dummy; } ;
struct tape_device {int /*<<< orphan*/  cdev_id; struct tape_3590_disc_data* discdata; } ;
struct tape_3590_disc_data {scalar_t__ read_back_op; } ;
struct irb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ READ_BACKWARD ; 
 scalar_t__ READ_PREVIOUS ; 
 int tape_3590_erp_retry (struct tape_device*,struct tape_request*,struct irb*) ; 
 int /*<<< orphan*/  tape_3590_read_opposite (struct tape_device*,struct tape_request*) ; 

__attribute__((used)) static int
tape_3590_erp_read_alternate(struct tape_device *device,
			     struct tape_request *request, struct irb *irb)
{
	struct tape_3590_disc_data *data;

	/*
	 * The issued Read Backward or Read Previous command is not
	 * supported by the device
	 * The recovery action should be to issue another command:
	 * Read Revious: if Read Backward is not supported
	 * Read Backward: if Read Previous is not supported
	 */
	data = device->discdata;
	if (data->read_back_op == READ_PREVIOUS) {
		DBF_EVENT(2, "(%08x): No support for READ_PREVIOUS command\n",
			  device->cdev_id);
		data->read_back_op = READ_BACKWARD;
	} else {
		DBF_EVENT(2, "(%08x): No support for READ_BACKWARD command\n",
			  device->cdev_id);
		data->read_back_op = READ_PREVIOUS;
	}
	tape_3590_read_opposite(device, request);
	return tape_3590_erp_retry(device, request, irb);
}