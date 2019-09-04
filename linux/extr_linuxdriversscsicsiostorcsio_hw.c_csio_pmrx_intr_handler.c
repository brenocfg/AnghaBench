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
struct intr_info {int member_0; char* member_1; int member_2; int member_3; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
#define  DB_OPTIONS_PAR_ERROR_F 132 
#define  IESPI_PAR_ERROR_F 131 
#define  OCSPI_PAR_ERROR_F 130 
#define  PMRX_E_PCMD_PAR_ERROR_F 129 
 int /*<<< orphan*/  PM_RX_INT_CAUSE_A ; 
#define  ZERO_E_CMD_ERROR_F 128 
 scalar_t__ csio_handle_intr_status (struct csio_hw*,int /*<<< orphan*/ ,struct intr_info*) ; 
 int /*<<< orphan*/  csio_hw_fatal_err (struct csio_hw*) ; 

__attribute__((used)) static void csio_pmrx_intr_handler(struct csio_hw *hw)
{
	static struct intr_info pmrx_intr_info[] = {
		{ ZERO_E_CMD_ERROR_F, "PMRX 0-length pcmd", -1, 1 },
		{ 0x3ffff0, "PMRX framing error", -1, 1 },
		{ OCSPI_PAR_ERROR_F, "PMRX ocspi parity error", -1, 1 },
		{ DB_OPTIONS_PAR_ERROR_F, "PMRX db_options parity error", -1,
		  1 },
		{ IESPI_PAR_ERROR_F, "PMRX iespi parity error", -1, 1 },
		{ PMRX_E_PCMD_PAR_ERROR_F, "PMRX e_pcmd parity error", -1, 1},
		{ 0, NULL, 0, 0 }
	};

	if (csio_handle_intr_status(hw, PM_RX_INT_CAUSE_A, pmrx_intr_info))
		csio_hw_fatal_err(hw);
}