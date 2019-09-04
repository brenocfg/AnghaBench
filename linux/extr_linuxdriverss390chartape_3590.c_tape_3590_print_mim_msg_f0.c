#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tape_device {TYPE_3__* cdev; } ;
struct TYPE_4__ {int emc; int mp; int md; int smc; } ;
struct TYPE_5__ {TYPE_1__ f70; } ;
struct tape_3590_sense {TYPE_2__ fmt; } ;
struct irb {scalar_t__ ecw; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
tape_3590_print_mim_msg_f0(struct tape_device *device, struct irb *irb)
{
	struct tape_3590_sense *sense;
	char *exception, *service;

	exception = kmalloc(BUFSIZE, GFP_ATOMIC);
	service = kmalloc(BUFSIZE, GFP_ATOMIC);

	if (!exception || !service)
		goto out_nomem;

	sense = (struct tape_3590_sense *) irb->ecw;
	/* Exception Message */
	switch (sense->fmt.f70.emc) {
	case 0x02:
		snprintf(exception, BUFSIZE, "Data degraded");
		break;
	case 0x03:
		snprintf(exception, BUFSIZE, "Data degraded in partion %i",
			sense->fmt.f70.mp);
		break;
	case 0x04:
		snprintf(exception, BUFSIZE, "Medium degraded");
		break;
	case 0x05:
		snprintf(exception, BUFSIZE, "Medium degraded in partition %i",
			sense->fmt.f70.mp);
		break;
	case 0x06:
		snprintf(exception, BUFSIZE, "Block 0 Error");
		break;
	case 0x07:
		snprintf(exception, BUFSIZE, "Medium Exception 0x%02x",
			sense->fmt.f70.md);
		break;
	default:
		snprintf(exception, BUFSIZE, "0x%02x",
			sense->fmt.f70.emc);
		break;
	}
	/* Service Message */
	switch (sense->fmt.f70.smc) {
	case 0x02:
		snprintf(service, BUFSIZE, "Reference Media maintenance "
			"procedure %i", sense->fmt.f70.md);
		break;
	default:
		snprintf(service, BUFSIZE, "0x%02x",
			sense->fmt.f70.smc);
		break;
	}

	dev_warn (&device->cdev->dev, "Tape media information: exception %s, "
		"service %s\n", exception, service);

out_nomem:
	kfree(exception);
	kfree(service);
}