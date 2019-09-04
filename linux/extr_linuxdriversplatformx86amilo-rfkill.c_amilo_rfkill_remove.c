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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amilo_rfkill_dev ; 
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amilo_rfkill_remove(struct platform_device *device)
{
	rfkill_unregister(amilo_rfkill_dev);
	rfkill_destroy(amilo_rfkill_dev);
	return 0;
}