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
struct sas_ha_struct {int /*<<< orphan*/  event_thres; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ssize_t phy_event_threshold_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);

	return scnprintf(buf, PAGE_SIZE, "%u\n", sha->event_thres);
}