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
struct snic {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 struct snic* shost_priv (int /*<<< orphan*/ ) ; 
 size_t snic_get_state (struct snic*) ; 
 char** snic_state_str ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t
snic_show_state(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{
	struct snic *snic = shost_priv(class_to_shost(dev));

	return snprintf(buf, PAGE_SIZE, "%s\n",
			snic_state_str[snic_get_state(snic)]);
}