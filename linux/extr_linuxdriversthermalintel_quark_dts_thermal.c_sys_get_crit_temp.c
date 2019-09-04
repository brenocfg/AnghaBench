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
struct thermal_zone_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QRK_DTS_ID_TP_CRITICAL ; 
 int _get_trip_temp (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline int sys_get_crit_temp(struct thermal_zone_device *tzd, int *temp)
{
	return _get_trip_temp(QRK_DTS_ID_TP_CRITICAL, temp);
}