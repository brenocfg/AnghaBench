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
struct timer_list {int dummy; } ;
struct nfc_dev {int /*<<< orphan*/  check_pres_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_pres_timer ; 
 struct nfc_dev* dev ; 
 struct nfc_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfc_check_pres_timeout(struct timer_list *t)
{
	struct nfc_dev *dev = from_timer(dev, t, check_pres_timer);

	schedule_work(&dev->check_pres_work);
}