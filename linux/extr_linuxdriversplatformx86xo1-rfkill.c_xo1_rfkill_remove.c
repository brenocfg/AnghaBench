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
struct rfkill {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct rfkill* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rfkill_destroy (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_unregister (struct rfkill*) ; 

__attribute__((used)) static int xo1_rfkill_remove(struct platform_device *pdev)
{
	struct rfkill *rfk = platform_get_drvdata(pdev);
	rfkill_unregister(rfk);
	rfkill_destroy(rfk);
	return 0;
}