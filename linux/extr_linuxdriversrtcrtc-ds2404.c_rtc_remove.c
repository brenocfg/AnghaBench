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
struct platform_device {int dummy; } ;
struct ds2404 {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmap_io ) (struct ds2404*) ;} ;

/* Variables and functions */
 struct ds2404* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct ds2404*) ; 

__attribute__((used)) static int rtc_remove(struct platform_device *dev)
{
	struct ds2404 *chip = platform_get_drvdata(dev);

	chip->ops->unmap_io(chip);

	return 0;
}