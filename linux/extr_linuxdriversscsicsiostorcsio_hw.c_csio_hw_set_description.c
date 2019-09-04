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
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
struct csio_hw {int /*<<< orphan*/  model_desc; int /*<<< orphan*/  hw_ver; } ;
struct TYPE_2__ {char* model_no; char* description; } ;

/* Variables and functions */
 scalar_t__ CSIO_ASIC_DEVID_PROTO_MASK ; 
 scalar_t__ CSIO_ASIC_DEVID_TYPE_MASK ; 
 size_t CSIO_T5_FCOE_ASIC ; 
 scalar_t__ CSIO_VENDOR_ID ; 
 TYPE_1__* csio_t5_fcoe_adapters ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
csio_hw_set_description(struct csio_hw *hw, uint16_t ven_id, uint16_t dev_id)
{
	uint32_t adap_type, prot_type;

	if (ven_id == CSIO_VENDOR_ID) {
		prot_type = (dev_id & CSIO_ASIC_DEVID_PROTO_MASK);
		adap_type = (dev_id & CSIO_ASIC_DEVID_TYPE_MASK);

		if (prot_type == CSIO_T5_FCOE_ASIC) {
			memcpy(hw->hw_ver,
			       csio_t5_fcoe_adapters[adap_type].model_no, 16);
			memcpy(hw->model_desc,
			       csio_t5_fcoe_adapters[adap_type].description,
			       32);
		} else {
			char tempName[32] = "Chelsio FCoE Controller";
			memcpy(hw->model_desc, tempName, 32);
		}
	}
}