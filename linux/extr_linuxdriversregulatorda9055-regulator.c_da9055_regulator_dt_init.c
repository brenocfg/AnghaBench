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
struct regulator_config {int dummy; } ;
struct platform_device {int dummy; } ;
struct da9055_regulator {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static inline int da9055_regulator_dt_init(struct platform_device *pdev,
				       struct da9055_regulator *regulator,
				       struct regulator_config *config,
				       int regid)
{
	return -ENODEV;
}