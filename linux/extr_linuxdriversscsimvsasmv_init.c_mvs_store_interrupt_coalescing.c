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
typedef  size_t u8 ;
struct sas_ha_struct {scalar_t__ lldd_ha; } ;
struct mvs_prv_info {size_t n_host; struct mvs_info** mvi; } ;
struct mvs_info {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* tune_interrupt ) (struct mvs_info*,unsigned int) ;} ;

/* Variables and functions */
 size_t EINVAL ; 
 TYPE_1__* MVS_CHIP_DISP ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 unsigned int interrupt_coalescing ; 
 int /*<<< orphan*/  mv_dprintk (char*,unsigned int) ; 
 int sscanf (char const*,char*,unsigned int*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (struct mvs_info*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t
mvs_store_interrupt_coalescing(struct device *cdev,
			struct device_attribute *attr,
			const char *buffer, size_t size)
{
	unsigned int val = 0;
	struct mvs_info *mvi = NULL;
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	u8 i, core_nr;
	if (buffer == NULL)
		return size;

	if (sscanf(buffer, "%u", &val) != 1)
		return -EINVAL;

	if (val >= 0x10000) {
		mv_dprintk("interrupt coalescing timer %d us is"
			"too long\n", val);
		return strlen(buffer);
	}

	interrupt_coalescing = val;

	core_nr = ((struct mvs_prv_info *)sha->lldd_ha)->n_host;
	mvi = ((struct mvs_prv_info *)sha->lldd_ha)->mvi[0];

	if (unlikely(!mvi))
		return -EINVAL;

	for (i = 0; i < core_nr; i++) {
		mvi = ((struct mvs_prv_info *)sha->lldd_ha)->mvi[i];
		if (MVS_CHIP_DISP->tune_interrupt)
			MVS_CHIP_DISP->tune_interrupt(mvi,
				interrupt_coalescing);
	}
	mv_dprintk("set interrupt coalescing time to %d us\n",
		interrupt_coalescing);
	return strlen(buffer);
}