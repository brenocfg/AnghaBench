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
struct nfc_target {int dummy; } ;
struct nfc_digital_dev {scalar_t__ curr_protocol; scalar_t__ poll_tech_count; } ;
struct nfc_dev {int dummy; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int EBUSY ; 
 struct nfc_digital_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int digital_activate_target(struct nfc_dev *nfc_dev,
				   struct nfc_target *target, __u32 protocol)
{
	struct nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);

	if (ddev->poll_tech_count) {
		pr_err("Can't activate a target while polling\n");
		return -EBUSY;
	}

	if (ddev->curr_protocol) {
		pr_err("A target is already active\n");
		return -EBUSY;
	}

	ddev->curr_protocol = protocol;

	return 0;
}