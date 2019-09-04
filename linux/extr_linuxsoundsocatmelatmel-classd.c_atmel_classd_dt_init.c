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
struct atmel_classd_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct atmel_classd_pdata* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct atmel_classd_pdata *
atmel_classd_dt_init(struct device *dev)
{
	return ERR_PTR(-EINVAL);
}