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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADP8870_BLDM4 ; 
 int /*<<< orphan*/  adp8870_show (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t adp8870_bl_l4_indoor_dim_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	return adp8870_show(dev, buf, ADP8870_BLDM4);
}