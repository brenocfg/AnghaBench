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
typedef  int /*<<< orphan*/  u32 ;
struct thermal_zone_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVS_TMON_TEMP_MAX ; 
 int AVS_TMON_TEMP_MIN ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int abs (int) ; 
 int /*<<< orphan*/  avs_tmon_get_coeffs (struct thermal_zone_device*,int*,int*) ; 

__attribute__((used)) static inline u32 avs_tmon_temp_to_code(struct thermal_zone_device *tz,
					int temp, bool low)
{
	int slope, offset;

	if (temp < AVS_TMON_TEMP_MIN)
		return AVS_TMON_TEMP_MAX; /* Maximum code value */

	avs_tmon_get_coeffs(tz, &slope, &offset);

	if (temp >= offset)
		return 0;	/* Minimum code value */

	if (low)
		return (u32)(DIV_ROUND_UP(offset - temp, abs(slope)));
	else
		return (u32)((offset - temp) / abs(slope));
}