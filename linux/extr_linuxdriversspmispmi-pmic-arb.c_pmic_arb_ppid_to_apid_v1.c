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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct spmi_pmic_arb {size_t* ppid_to_apid; TYPE_1__* apid_data; scalar_t__ cnfg; int /*<<< orphan*/  mapping_table_valid; int /*<<< orphan*/ * mapping_table; } ;
struct TYPE_2__ {size_t ppid; } ;

/* Variables and functions */
 size_t BIT (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 size_t PMIC_ARB_APID_VALID ; 
 int /*<<< orphan*/  SPMI_MAPPING_BIT_INDEX (int /*<<< orphan*/ ) ; 
 scalar_t__ SPMI_MAPPING_BIT_IS_0_FLAG (int /*<<< orphan*/ ) ; 
 void* SPMI_MAPPING_BIT_IS_0_RESULT (int /*<<< orphan*/ ) ; 
 scalar_t__ SPMI_MAPPING_BIT_IS_1_FLAG (int /*<<< orphan*/ ) ; 
 void* SPMI_MAPPING_BIT_IS_1_RESULT (int /*<<< orphan*/ ) ; 
 scalar_t__ SPMI_MAPPING_TABLE_REG (int) ; 
 int SPMI_MAPPING_TABLE_TREE_DEPTH ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmic_arb_ppid_to_apid_v1(struct spmi_pmic_arb *pmic_arb, u16 ppid)
{
	u32 *mapping_table = pmic_arb->mapping_table;
	int index = 0, i;
	u16 apid_valid;
	u16 apid;
	u32 data;

	apid_valid = pmic_arb->ppid_to_apid[ppid];
	if (apid_valid & PMIC_ARB_APID_VALID) {
		apid = apid_valid & ~PMIC_ARB_APID_VALID;
		return apid;
	}

	for (i = 0; i < SPMI_MAPPING_TABLE_TREE_DEPTH; ++i) {
		if (!test_and_set_bit(index, pmic_arb->mapping_table_valid))
			mapping_table[index] = readl_relaxed(pmic_arb->cnfg +
						SPMI_MAPPING_TABLE_REG(index));

		data = mapping_table[index];

		if (ppid & BIT(SPMI_MAPPING_BIT_INDEX(data))) {
			if (SPMI_MAPPING_BIT_IS_1_FLAG(data)) {
				index = SPMI_MAPPING_BIT_IS_1_RESULT(data);
			} else {
				apid = SPMI_MAPPING_BIT_IS_1_RESULT(data);
				pmic_arb->ppid_to_apid[ppid]
					= apid | PMIC_ARB_APID_VALID;
				pmic_arb->apid_data[apid].ppid = ppid;
				return apid;
			}
		} else {
			if (SPMI_MAPPING_BIT_IS_0_FLAG(data)) {
				index = SPMI_MAPPING_BIT_IS_0_RESULT(data);
			} else {
				apid = SPMI_MAPPING_BIT_IS_0_RESULT(data);
				pmic_arb->ppid_to_apid[ppid]
					= apid | PMIC_ARB_APID_VALID;
				pmic_arb->apid_data[apid].ppid = ppid;
				return apid;
			}
		}
	}

	return -ENODEV;
}