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
struct tps65217_charger {scalar_t__ poll_task; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 struct tps65217_charger* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int tps65217_charger_remove(struct platform_device *pdev)
{
	struct tps65217_charger *charger = platform_get_drvdata(pdev);

	if (charger->poll_task)
		kthread_stop(charger->poll_task);

	return 0;
}