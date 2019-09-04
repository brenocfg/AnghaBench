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
struct TYPE_2__ {scalar_t__ xpt_type; } ;
struct snic {scalar_t__ link_status; int /*<<< orphan*/  vdev; TYPE_1__ config; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ SNIC_DAS ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 struct snic* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ svnic_dev_link_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
snic_show_link_state(struct device *dev,
		     struct device_attribute *attr,
		     char *buf)
{
	struct snic *snic = shost_priv(class_to_shost(dev));

	if (snic->config.xpt_type == SNIC_DAS)
		snic->link_status = svnic_dev_link_status(snic->vdev);

	return snprintf(buf, PAGE_SIZE, "%s\n",
			(snic->link_status) ? "Link Up" : "Link Down");
}