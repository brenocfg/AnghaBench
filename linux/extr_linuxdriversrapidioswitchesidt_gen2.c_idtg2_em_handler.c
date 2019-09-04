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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rio_dev {scalar_t__ em_efptr; } ;

/* Variables and functions */
 scalar_t__ IDT_ISLTL_ADDRESS_CAP ; 
 scalar_t__ IDT_PORT_ISERR_DET (int /*<<< orphan*/ ) ; 
 int REM_LTL_ERR_IMPSPEC ; 
 int REM_PED_IMPL_SPEC ; 
 scalar_t__ RIO_EM_LTL_ERR_DETECT ; 
 scalar_t__ RIO_EM_PN_ERR_DETECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  rio_name (struct rio_dev*) ; 
 int /*<<< orphan*/  rio_read_config_32 (struct rio_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  rio_write_config_32 (struct rio_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
idtg2_em_handler(struct rio_dev *rdev, u8 portnum)
{
	u32 regval, em_perrdet, em_ltlerrdet;

	rio_read_config_32(rdev,
		rdev->em_efptr + RIO_EM_LTL_ERR_DETECT, &em_ltlerrdet);
	if (em_ltlerrdet) {
		/* Service Logical/Transport Layer Error(s) */
		if (em_ltlerrdet & REM_LTL_ERR_IMPSPEC) {
			/* Implementation specific error reported */
			rio_read_config_32(rdev,
					IDT_ISLTL_ADDRESS_CAP, &regval);

			pr_debug("RIO: %s Implementation Specific LTL errors" \
				 " 0x%x @(0x%x)\n",
				 rio_name(rdev), em_ltlerrdet, regval);

			/* Clear implementation specific address capture CSR */
			rio_write_config_32(rdev, IDT_ISLTL_ADDRESS_CAP, 0);

		}
	}

	rio_read_config_32(rdev,
		rdev->em_efptr + RIO_EM_PN_ERR_DETECT(portnum), &em_perrdet);
	if (em_perrdet) {
		/* Service Port-Level Error(s) */
		if (em_perrdet & REM_PED_IMPL_SPEC) {
			/* Implementation Specific port error reported */

			/* Get IS errors reported */
			rio_read_config_32(rdev,
					IDT_PORT_ISERR_DET(portnum), &regval);

			pr_debug("RIO: %s Implementation Specific Port" \
				 " errors 0x%x\n", rio_name(rdev), regval);

			/* Clear all implementation specific events */
			rio_write_config_32(rdev,
					IDT_PORT_ISERR_DET(portnum), 0);
		}
	}

	return 0;
}