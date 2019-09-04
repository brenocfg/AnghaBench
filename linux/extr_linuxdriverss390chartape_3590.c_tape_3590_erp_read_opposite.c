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
struct tape_request {int op; } ;
struct tape_device {int dummy; } ;
struct irb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
#define  TO_RBA 129 
#define  TO_RFO 128 
 int tape_3590_erp_failed (struct tape_device*,struct tape_request*,struct irb*,int /*<<< orphan*/ ) ; 
 int tape_3590_erp_retry (struct tape_device*,struct tape_request*,struct irb*) ; 
 int /*<<< orphan*/  tape_3590_read_opposite (struct tape_device*,struct tape_request*) ; 

__attribute__((used)) static int
tape_3590_erp_read_opposite(struct tape_device *device,
			    struct tape_request *request, struct irb *irb)
{
	switch (request->op) {
	case TO_RFO:
		/*
		 * We did read forward, but the data could not be read.
		 * We will read backward and then skip forward again.
		 */
		tape_3590_read_opposite(device, request);
		return tape_3590_erp_retry(device, request, irb);
	case TO_RBA:
		/* We tried to read forward and backward, but hat no success */
		return tape_3590_erp_failed(device, request, irb, -EIO);
		break;
	default:
		return tape_3590_erp_failed(device, request, irb, -EIO);
	}
}