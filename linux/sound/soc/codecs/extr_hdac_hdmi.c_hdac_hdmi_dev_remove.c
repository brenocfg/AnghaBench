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
struct hdac_device {int /*<<< orphan*/  addr; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_dapm_works (struct hdac_device*) ; 
 int /*<<< orphan*/  snd_hdac_display_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdac_hdmi_dev_remove(struct hdac_device *hdev)
{
	clear_dapm_works(hdev);
	snd_hdac_display_power(hdev->bus, hdev->addr, false);

	return 0;
}