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
typedef  int u32 ;
struct rapl_domain {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  floor_freq_reg_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MBI_UNIT_PMC ; 
 int /*<<< orphan*/  MBI_CR_READ ; 
 int /*<<< orphan*/  MBI_CR_WRITE ; 
 int /*<<< orphan*/  iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  iosf_mbi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_1__* rapl_defaults ; 

__attribute__((used)) static void set_floor_freq_atom(struct rapl_domain *rd, bool enable)
{
	static u32 power_ctrl_orig_val;
	u32 mdata;

	if (!rapl_defaults->floor_freq_reg_addr) {
		pr_err("Invalid floor frequency config register\n");
		return;
	}

	if (!power_ctrl_orig_val)
		iosf_mbi_read(BT_MBI_UNIT_PMC, MBI_CR_READ,
			      rapl_defaults->floor_freq_reg_addr,
			      &power_ctrl_orig_val);
	mdata = power_ctrl_orig_val;
	if (enable) {
		mdata &= ~(0x7f << 8);
		mdata |= 1 << 8;
	}
	iosf_mbi_write(BT_MBI_UNIT_PMC, MBI_CR_WRITE,
		       rapl_defaults->floor_freq_reg_addr, mdata);
}