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
typedef  int u16 ;
typedef  enum cros_ec_lpc_mec_emi_access_mode { ____Placeholder_cros_ec_lpc_mec_emi_access_mode } cros_ec_lpc_mec_emi_access_mode ;

/* Variables and functions */
 int /*<<< orphan*/  MEC_EMI_EC_ADDRESS_B0 ; 
 int /*<<< orphan*/  MEC_EMI_EC_ADDRESS_B1 ; 
 scalar_t__ MEC_EMI_RANGE_START ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cros_ec_lpc_mec_emi_write_address(u16 addr,
			enum cros_ec_lpc_mec_emi_access_mode access_type)
{
	/* Address relative to start of EMI range */
	addr -= MEC_EMI_RANGE_START;
	outb((addr & 0xfc) | access_type, MEC_EMI_EC_ADDRESS_B0);
	outb((addr >> 8) & 0x7f, MEC_EMI_EC_ADDRESS_B1);
}