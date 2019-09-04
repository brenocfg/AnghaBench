#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_4__ {int phys_addr; } ;
struct TYPE_3__ {int phys_addr; } ;
struct esas2r_adapter {int max_vdareq_size; int uncached_phys; int* outbound_copy; int last_write; int last_read; int list_size; int /*<<< orphan*/  flags2; int /*<<< orphan*/  flags; int /*<<< orphan*/ * uncached; TYPE_2__ outbound_list_md; TYPE_1__ inbound_list_md; int /*<<< orphan*/  build_sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF2_VDA_POWER_DOWN ; 
 int /*<<< orphan*/  AF_CHPRST_DETECTED ; 
 int /*<<< orphan*/  AF_COMM_LIST_TOGGLE ; 
 int /*<<< orphan*/  AF_LEGACY_SGE_MODE ; 
 int DRBL_ENB_MASK ; 
 int DRBL_FORCE_INT ; 
 int DRBL_FW_VER_0 ; 
 int DRBL_FW_VER_1 ; 
 int DRBL_FW_VER_MSK ; 
 int DRBL_MSG_IFC_DOWN ; 
 int DRBL_MSG_IFC_INIT ; 
 int DRBL_POWER_DOWN ; 
 int ESAS2R_INT_DIS_MASK ; 
 int /*<<< orphan*/  MU_DOORBELL_IN ; 
 int /*<<< orphan*/  MU_DOORBELL_IN_ENB ; 
 int /*<<< orphan*/  MU_DOORBELL_OUT ; 
 int /*<<< orphan*/  MU_DOORBELL_OUT_ENB ; 
 int MU_ILC_DYNAMIC_SRC ; 
 int MU_ILC_ENABLE ; 
 int MU_ILC_ENTRY_4_DW ; 
 int MU_ILC_ENTRY_MASK ; 
 int MU_ILC_NUMBER_MASK ; 
 int MU_ILC_NUMBER_SHIFT ; 
 int MU_ILIC_DEST ; 
 int MU_ILIC_DEST_DDR ; 
 int MU_ILIC_LIST ; 
 int MU_ILIC_LIST_F0 ; 
 int MU_ILR_TOGGLE ; 
 int MU_ILW_TOGGLE ; 
 int /*<<< orphan*/  MU_INT_MASK_OUT ; 
 int /*<<< orphan*/  MU_IN_LIST_ADDR_HI ; 
 int /*<<< orphan*/  MU_IN_LIST_ADDR_LO ; 
 int /*<<< orphan*/  MU_IN_LIST_CONFIG ; 
 int /*<<< orphan*/  MU_IN_LIST_IFC_CONFIG ; 
 int /*<<< orphan*/  MU_IN_LIST_READ ; 
 int /*<<< orphan*/  MU_IN_LIST_WRITE ; 
 int MU_OLC_ENABLE ; 
 int MU_OLC_ENTRY_4_DW ; 
 int MU_OLC_ENTRY_MASK ; 
 int MU_OLC_NUMBER_MASK ; 
 int MU_OLC_NUMBER_SHIFT ; 
 int MU_OLC_TOGGLE ; 
 int MU_OLIC_LIST ; 
 int MU_OLIC_LIST_F0 ; 
 int MU_OLIC_SOURCE ; 
 int MU_OLIC_SOURCE_DDR ; 
 int MU_OLIS_MASK ; 
 int MU_OLW_TOGGLE ; 
 int /*<<< orphan*/  MU_OUT_LIST_ADDR_HI ; 
 int /*<<< orphan*/  MU_OUT_LIST_ADDR_LO ; 
 int /*<<< orphan*/  MU_OUT_LIST_CONFIG ; 
 int /*<<< orphan*/  MU_OUT_LIST_COPY ; 
 int /*<<< orphan*/  MU_OUT_LIST_COPY_PTR_HI ; 
 int /*<<< orphan*/  MU_OUT_LIST_COPY_PTR_LO ; 
 int /*<<< orphan*/  MU_OUT_LIST_IFC_CONFIG ; 
 int /*<<< orphan*/  MU_OUT_LIST_INT_MASK ; 
 int /*<<< orphan*/  MU_OUT_LIST_WRITE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_bugon () ; 
 int /*<<< orphan*/  esas2r_build_sg_list_prd ; 
 int /*<<< orphan*/  esas2r_build_sg_list_sge ; 
 int /*<<< orphan*/  esas2r_flush_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_force_interrupt (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_hdebug (char*) ; 
 int esas2r_read_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ) ; 
 int esas2r_set_degraded_mode (struct esas2r_adapter*,char*) ; 
 int /*<<< orphan*/  esas2r_write_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int upper_32_bits (int) ; 

bool esas2r_check_adapter(struct esas2r_adapter *a)
{
	u32 starttime;
	u32 doorbell;
	u64 ppaddr;
	u32 dw;

	/*
	 * if the chip reset detected flag is set, we can bypass a bunch of
	 * stuff.
	 */
	if (test_bit(AF_CHPRST_DETECTED, &a->flags))
		goto skip_chip_reset;

	/*
	 * BEFORE WE DO ANYTHING, disable the chip interrupts!  the boot driver
	 * may have left them enabled or we may be recovering from a fault.
	 */
	esas2r_write_register_dword(a, MU_INT_MASK_OUT, ESAS2R_INT_DIS_MASK);
	esas2r_flush_register_dword(a, MU_INT_MASK_OUT);

	/*
	 * wait for the firmware to become ready by forcing an interrupt and
	 * waiting for a response.
	 */
	starttime = jiffies_to_msecs(jiffies);

	while (true) {
		esas2r_force_interrupt(a);
		doorbell = esas2r_read_register_dword(a, MU_DOORBELL_OUT);
		if (doorbell == 0xFFFFFFFF) {
			/*
			 * Give the firmware up to two seconds to enable
			 * register access after a reset.
			 */
			if ((jiffies_to_msecs(jiffies) - starttime) > 2000)
				return esas2r_set_degraded_mode(a,
								"unable to access registers");
		} else if (doorbell & DRBL_FORCE_INT) {
			u32 ver = (doorbell & DRBL_FW_VER_MSK);

			/*
			 * This driver supports version 0 and version 1 of
			 * the API
			 */
			esas2r_write_register_dword(a, MU_DOORBELL_OUT,
						    doorbell);

			if (ver == DRBL_FW_VER_0) {
				set_bit(AF_LEGACY_SGE_MODE, &a->flags);

				a->max_vdareq_size = 128;
				a->build_sgl = esas2r_build_sg_list_sge;
			} else if (ver == DRBL_FW_VER_1) {
				clear_bit(AF_LEGACY_SGE_MODE, &a->flags);

				a->max_vdareq_size = 1024;
				a->build_sgl = esas2r_build_sg_list_prd;
			} else {
				return esas2r_set_degraded_mode(a,
								"unknown firmware version");
			}
			break;
		}

		schedule_timeout_interruptible(msecs_to_jiffies(100));

		if ((jiffies_to_msecs(jiffies) - starttime) > 180000) {
			esas2r_hdebug("FW ready TMO");
			esas2r_bugon();

			return esas2r_set_degraded_mode(a,
							"firmware start has timed out");
		}
	}

	/* purge any asynchronous events since we will repost them later */
	esas2r_write_register_dword(a, MU_DOORBELL_IN, DRBL_MSG_IFC_DOWN);
	starttime = jiffies_to_msecs(jiffies);

	while (true) {
		doorbell = esas2r_read_register_dword(a, MU_DOORBELL_OUT);
		if (doorbell & DRBL_MSG_IFC_DOWN) {
			esas2r_write_register_dword(a, MU_DOORBELL_OUT,
						    doorbell);
			break;
		}

		schedule_timeout_interruptible(msecs_to_jiffies(50));

		if ((jiffies_to_msecs(jiffies) - starttime) > 3000) {
			esas2r_hdebug("timeout waiting for interface down");
			break;
		}
	}
skip_chip_reset:
	/*
	 * first things first, before we go changing any of these registers
	 * disable the communication lists.
	 */
	dw = esas2r_read_register_dword(a, MU_IN_LIST_CONFIG);
	dw &= ~MU_ILC_ENABLE;
	esas2r_write_register_dword(a, MU_IN_LIST_CONFIG, dw);
	dw = esas2r_read_register_dword(a, MU_OUT_LIST_CONFIG);
	dw &= ~MU_OLC_ENABLE;
	esas2r_write_register_dword(a, MU_OUT_LIST_CONFIG, dw);

	/* configure the communication list addresses */
	ppaddr = a->inbound_list_md.phys_addr;
	esas2r_write_register_dword(a, MU_IN_LIST_ADDR_LO,
				    lower_32_bits(ppaddr));
	esas2r_write_register_dword(a, MU_IN_LIST_ADDR_HI,
				    upper_32_bits(ppaddr));
	ppaddr = a->outbound_list_md.phys_addr;
	esas2r_write_register_dword(a, MU_OUT_LIST_ADDR_LO,
				    lower_32_bits(ppaddr));
	esas2r_write_register_dword(a, MU_OUT_LIST_ADDR_HI,
				    upper_32_bits(ppaddr));
	ppaddr = a->uncached_phys +
		 ((u8 *)a->outbound_copy - a->uncached);
	esas2r_write_register_dword(a, MU_OUT_LIST_COPY_PTR_LO,
				    lower_32_bits(ppaddr));
	esas2r_write_register_dword(a, MU_OUT_LIST_COPY_PTR_HI,
				    upper_32_bits(ppaddr));

	/* reset the read and write pointers */
	*a->outbound_copy =
		a->last_write =
			a->last_read = a->list_size - 1;
	set_bit(AF_COMM_LIST_TOGGLE, &a->flags);
	esas2r_write_register_dword(a, MU_IN_LIST_WRITE, MU_ILW_TOGGLE |
				    a->last_write);
	esas2r_write_register_dword(a, MU_OUT_LIST_COPY, MU_OLC_TOGGLE |
				    a->last_write);
	esas2r_write_register_dword(a, MU_IN_LIST_READ, MU_ILR_TOGGLE |
				    a->last_write);
	esas2r_write_register_dword(a, MU_OUT_LIST_WRITE,
				    MU_OLW_TOGGLE | a->last_write);

	/* configure the interface select fields */
	dw = esas2r_read_register_dword(a, MU_IN_LIST_IFC_CONFIG);
	dw &= ~(MU_ILIC_LIST | MU_ILIC_DEST);
	esas2r_write_register_dword(a, MU_IN_LIST_IFC_CONFIG,
				    (dw | MU_ILIC_LIST_F0 | MU_ILIC_DEST_DDR));
	dw = esas2r_read_register_dword(a, MU_OUT_LIST_IFC_CONFIG);
	dw &= ~(MU_OLIC_LIST | MU_OLIC_SOURCE);
	esas2r_write_register_dword(a, MU_OUT_LIST_IFC_CONFIG,
				    (dw | MU_OLIC_LIST_F0 |
				     MU_OLIC_SOURCE_DDR));

	/* finish configuring the communication lists */
	dw = esas2r_read_register_dword(a, MU_IN_LIST_CONFIG);
	dw &= ~(MU_ILC_ENTRY_MASK | MU_ILC_NUMBER_MASK);
	dw |= MU_ILC_ENTRY_4_DW | MU_ILC_DYNAMIC_SRC
	      | (a->list_size << MU_ILC_NUMBER_SHIFT);
	esas2r_write_register_dword(a, MU_IN_LIST_CONFIG, dw);
	dw = esas2r_read_register_dword(a, MU_OUT_LIST_CONFIG);
	dw &= ~(MU_OLC_ENTRY_MASK | MU_OLC_NUMBER_MASK);
	dw |= MU_OLC_ENTRY_4_DW | (a->list_size << MU_OLC_NUMBER_SHIFT);
	esas2r_write_register_dword(a, MU_OUT_LIST_CONFIG, dw);

	/*
	 * notify the firmware that we're done setting up the communication
	 * list registers.  wait here until the firmware is done configuring
	 * its lists.  it will signal that it is done by enabling the lists.
	 */
	esas2r_write_register_dword(a, MU_DOORBELL_IN, DRBL_MSG_IFC_INIT);
	starttime = jiffies_to_msecs(jiffies);

	while (true) {
		doorbell = esas2r_read_register_dword(a, MU_DOORBELL_OUT);
		if (doorbell & DRBL_MSG_IFC_INIT) {
			esas2r_write_register_dword(a, MU_DOORBELL_OUT,
						    doorbell);
			break;
		}

		schedule_timeout_interruptible(msecs_to_jiffies(100));

		if ((jiffies_to_msecs(jiffies) - starttime) > 3000) {
			esas2r_hdebug(
				"timeout waiting for communication list init");
			esas2r_bugon();
			return esas2r_set_degraded_mode(a,
							"timeout waiting for communication list init");
		}
	}

	/*
	 * flag whether the firmware supports the power down doorbell.  we
	 * determine this by reading the inbound doorbell enable mask.
	 */
	doorbell = esas2r_read_register_dword(a, MU_DOORBELL_IN_ENB);
	if (doorbell & DRBL_POWER_DOWN)
		set_bit(AF2_VDA_POWER_DOWN, &a->flags2);
	else
		clear_bit(AF2_VDA_POWER_DOWN, &a->flags2);

	/*
	 * enable assertion of outbound queue and doorbell interrupts in the
	 * main interrupt cause register.
	 */
	esas2r_write_register_dword(a, MU_OUT_LIST_INT_MASK, MU_OLIS_MASK);
	esas2r_write_register_dword(a, MU_DOORBELL_OUT_ENB, DRBL_ENB_MASK);
	return true;
}