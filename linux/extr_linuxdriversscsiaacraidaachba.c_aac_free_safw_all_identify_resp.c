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
typedef  int /*<<< orphan*/  u32 ;
struct aac_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aac_free_safw_identify_resp (struct aac_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aac_get_safw_phys_bus (struct aac_dev*,int) ; 
 int aac_get_safw_phys_lun_count (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_get_safw_phys_target (struct aac_dev*,int) ; 

__attribute__((used)) static inline void aac_free_safw_all_identify_resp(struct aac_dev *dev,
	int lun_count)
{
	int luns;
	int i;
	u32 bus;
	u32 target;

	luns = aac_get_safw_phys_lun_count(dev);

	if (luns < lun_count)
		lun_count = luns;
	else if (lun_count < 0)
		lun_count = luns;

	for (i = 0; i < lun_count; i++) {
		bus = aac_get_safw_phys_bus(dev, i);
		target = aac_get_safw_phys_target(dev, i);

		aac_free_safw_identify_resp(dev, bus, target);
	}
}