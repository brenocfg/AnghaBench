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

/* Variables and functions */

__attribute__((used)) static void fbtft_device_pdev_release(struct device *dev)
{
/* Needed to silence this message:
 * Device 'xxx' does not have a release() function,
 * it is broken and must be fixed
 */
}