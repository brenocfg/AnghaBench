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
struct hisi_hba {void* sata_dev_bitmap; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int HISI_MAX_SATA_SUPPORT_V2_HW ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,unsigned int) ; 
 unsigned int find_first_zero_bit (void*,unsigned int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,void*) ; 

__attribute__((used)) static bool sata_index_alloc_v2_hw(struct hisi_hba *hisi_hba, int *idx)
{
	unsigned int index;
	struct device *dev = hisi_hba->dev;
	void *bitmap = hisi_hba->sata_dev_bitmap;

	index = find_first_zero_bit(bitmap, HISI_MAX_SATA_SUPPORT_V2_HW);
	if (index >= HISI_MAX_SATA_SUPPORT_V2_HW) {
		dev_warn(dev, "alloc sata index failed, index=%d\n", index);
		return false;
	}

	set_bit(index, bitmap);
	*idx = index;
	return true;
}