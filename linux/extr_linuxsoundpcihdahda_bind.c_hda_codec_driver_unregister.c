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
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct hda_codec_driver {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 

void hda_codec_driver_unregister(struct hda_codec_driver *drv)
{
	driver_unregister(&drv->core.driver);
}