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
struct tsens_sensor {int /*<<< orphan*/  id; struct tsens_device* tmdev; } ;
struct tsens_device {TYPE_1__* ops; } ;
typedef  enum thermal_trend { ____Placeholder_thermal_trend } thermal_trend ;
struct TYPE_2__ {int (* get_trend ) (struct tsens_device*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int stub1 (struct tsens_device*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int tsens_get_trend(void *p, int trip, enum thermal_trend *trend)
{
	const struct tsens_sensor *s = p;
	struct tsens_device *tmdev = s->tmdev;

	if (tmdev->ops->get_trend)
		return  tmdev->ops->get_trend(tmdev, s->id, trend);

	return -ENOTSUPP;
}