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
struct device {int dummy; } ;
struct atm_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct atm_dev*) ; 
 struct atm_dev* to_atm_dev (struct device*) ; 

__attribute__((used)) static void atm_release(struct device *cdev)
{
	struct atm_dev *adev = to_atm_dev(cdev);

	kfree(adev);
}