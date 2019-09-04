#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zcrypt_card {int dummy; } ;
struct ap_device {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {struct zcrypt_card* private; } ;

/* Variables and functions */
 TYPE_1__* to_ap_card (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcrypt_card_unregister (struct zcrypt_card*) ; 

__attribute__((used)) static void zcrypt_cex2a_card_remove(struct ap_device *ap_dev)
{
	struct zcrypt_card *zc = to_ap_card(&ap_dev->device)->private;

	if (zc)
		zcrypt_card_unregister(zc);
}