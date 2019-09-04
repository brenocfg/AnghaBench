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
struct wmi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dell_wmi_input_destroy (struct wmi_device*) ; 

__attribute__((used)) static int dell_wmi_remove(struct wmi_device *wdev)
{
	dell_wmi_input_destroy(wdev);
	return 0;
}