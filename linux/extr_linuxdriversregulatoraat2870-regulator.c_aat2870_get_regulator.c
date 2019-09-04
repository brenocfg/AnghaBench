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
struct TYPE_2__ {int id; } ;
struct aat2870_regulator {int enable_shift; int enable_mask; int voltage_shift; int voltage_mask; int /*<<< orphan*/  voltage_addr; int /*<<< orphan*/  enable_addr; TYPE_1__ desc; } ;

/* Variables and functions */
 int AAT2870_ID_LDOA ; 
 int /*<<< orphan*/  AAT2870_LDO_AB ; 
 int /*<<< orphan*/  AAT2870_LDO_CD ; 
 int /*<<< orphan*/  AAT2870_LDO_EN ; 
 int ARRAY_SIZE (struct aat2870_regulator*) ; 
 struct aat2870_regulator* aat2870_regulators ; 

__attribute__((used)) static struct aat2870_regulator *aat2870_get_regulator(int id)
{
	struct aat2870_regulator *ri = NULL;
	int i;

	for (i = 0; i < ARRAY_SIZE(aat2870_regulators); i++) {
		ri = &aat2870_regulators[i];
		if (ri->desc.id == id)
			break;
	}

	if (i == ARRAY_SIZE(aat2870_regulators))
		return NULL;

	ri->enable_addr = AAT2870_LDO_EN;
	ri->enable_shift = id - AAT2870_ID_LDOA;
	ri->enable_mask = 0x1 << ri->enable_shift;

	ri->voltage_addr = (id - AAT2870_ID_LDOA) / 2 ?
			   AAT2870_LDO_CD : AAT2870_LDO_AB;
	ri->voltage_shift = (id - AAT2870_ID_LDOA) % 2 ? 0 : 4;
	ri->voltage_mask = 0xF << ri->voltage_shift;

	return ri;
}