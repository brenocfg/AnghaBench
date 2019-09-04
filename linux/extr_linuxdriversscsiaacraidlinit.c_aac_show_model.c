#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {char* adapter_type_text; } ;
struct aac_dev {size_t cardtype; TYPE_1__ supplement_adapter_info; } ;
typedef  int ssize_t ;
struct TYPE_6__ {char* model; } ;
struct TYPE_5__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_3__* aac_drivers ; 
 TYPE_2__* class_to_shost (struct device*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t aac_show_model(struct device *device,
			      struct device_attribute *attr, char *buf)
{
	struct aac_dev *dev = (struct aac_dev*)class_to_shost(device)->hostdata;
	int len;

	if (dev->supplement_adapter_info.adapter_type_text[0]) {
		char *cp = dev->supplement_adapter_info.adapter_type_text;
		while (*cp && *cp != ' ')
			++cp;
		while (*cp == ' ')
			++cp;
		len = snprintf(buf, PAGE_SIZE, "%s\n", cp);
	} else
		len = snprintf(buf, PAGE_SIZE, "%s\n",
		  aac_drivers[dev->cardtype].model);
	return len;
}