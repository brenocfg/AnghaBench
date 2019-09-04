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
struct act8865_platform_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int act8865_pdata_from_dt(struct device *dev,
					struct act8865_platform_data *pdata,
					unsigned long type)
{
	return 0;
}