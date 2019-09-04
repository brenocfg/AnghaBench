#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtl8169_private {TYPE_1__* rtl_fw; } ;
struct TYPE_4__ {int /*<<< orphan*/  fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_1__*) ; 
 TYPE_1__* RTL_FIRMWARE_UNKNOWN ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_release_firmware(struct rtl8169_private *tp)
{
	if (!IS_ERR_OR_NULL(tp->rtl_fw)) {
		release_firmware(tp->rtl_fw->fw);
		kfree(tp->rtl_fw);
	}
	tp->rtl_fw = RTL_FIRMWARE_UNKNOWN;
}