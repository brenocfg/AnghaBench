#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct tape_request {int dummy; } ;
struct tape_device {TYPE_1__* cdev; } ;
struct TYPE_4__ {char* data; } ;
struct tape_3590_sense {TYPE_2__ fmt; } ;
struct irb {scalar_t__ ecw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EKEYREJECTED ; 
 int /*<<< orphan*/  ENOKEY ; 
 int /*<<< orphan*/  ENOTCONN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int tape_3590_erp_basic (struct tape_device*,struct tape_request*,struct irb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tape_3590_crypt_error(struct tape_device *device,
				 struct tape_request *request, struct irb *irb)
{
	u8 cu_rc;
	u16 ekm_rc2;
	char *sense;

	sense = ((struct tape_3590_sense *) irb->ecw)->fmt.data;
	cu_rc = sense[0];
	ekm_rc2 = *((u16*) &sense[10]);
	if ((cu_rc == 0) && (ekm_rc2 == 0xee31))
		/* key not defined on EKM */
		return tape_3590_erp_basic(device, request, irb, -EKEYREJECTED);
	if ((cu_rc == 1) || (cu_rc == 2))
		/* No connection to EKM */
		return tape_3590_erp_basic(device, request, irb, -ENOTCONN);

	dev_err (&device->cdev->dev, "The tape unit failed to obtain the "
		"encryption key from EKM\n");

	return tape_3590_erp_basic(device, request, irb, -ENOKEY);
}