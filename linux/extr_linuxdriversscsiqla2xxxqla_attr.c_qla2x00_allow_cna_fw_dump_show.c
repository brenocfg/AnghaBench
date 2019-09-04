#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {TYPE_3__* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;
struct TYPE_5__ {scalar_t__ allow_cna_fw_dump; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_P3P_TYPE (TYPE_3__*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
qla2x00_allow_cna_fw_dump_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	if (!IS_P3P_TYPE(vha->hw))
		return scnprintf(buf, PAGE_SIZE, "\n");
	else
		return scnprintf(buf, PAGE_SIZE, "%s\n",
		    vha->hw->allow_cna_fw_dump ? "true" : "false");
}