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
struct TYPE_2__ {int /*<<< orphan*/  mad_version; } ;
struct ibmvscsi_host_data {TYPE_1__ madapter_info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 struct ibmvscsi_host_data* shost_priv (struct Scsi_Host*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t show_host_mad_version(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct ibmvscsi_host_data *hostdata = shost_priv(shost);
	int len;

	len = snprintf(buf, PAGE_SIZE, "%d\n",
		       be32_to_cpu(hostdata->madapter_info.mad_version));
	return len;
}