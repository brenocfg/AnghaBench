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
typedef  int /*<<< orphan*/  umode_t ;
struct kobject {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {scalar_t__ secm; } ;

/* Variables and functions */
 TYPE_1__ css_chsc_characteristics ; 

__attribute__((used)) static umode_t cm_enable_mode(struct kobject *kobj, struct attribute *attr,
			      int index)
{
	return css_chsc_characteristics.secm ? attr->mode : 0;
}