#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int top_addr; } ;
union wrap_top_dir_u {scalar_t__ val; TYPE_9__ f; } ;
struct TYPE_17__ {int start_addr; } ;
union wrap_start_dir_u {scalar_t__ val; TYPE_8__ f; } ;
struct TYPE_14__ {int ad_inc_a; int ad_inc_b; scalar_t__ rd_data_rdy_b; scalar_t__ rd_data_rdy_a; } ;
union intf_cntl_u {scalar_t__ val; TYPE_5__ f; } ;
struct TYPE_15__ {int access_ind_addr_a; int access_ind_addr_b; int access_scratch_reg; scalar_t__ transition_size; } ;
union cpu_defaults_u {scalar_t__ val; TYPE_6__ f; } ;
struct TYPE_11__ {int en_dword_split_to_rbbm; int dis_timeout_during_rbbm; scalar_t__ dis_packer_ful_during_rbbm_timeout; } ;
union cif_write_dbg_u {void* val; TYPE_2__ f; } ;
struct TYPE_12__ {int dis_rd_same_byte_to_trig_fetch; } ;
union cif_read_dbg_u {void* val; TYPE_3__ f; } ;
union cif_io_u {scalar_t__ val; } ;
struct TYPE_13__ {int dis_system_bits; int dis_mr; int intb_oe; int interrupt_active_high; scalar_t__ en_wait_to_compensate_dq_prop_dly; } ;
union cif_cntl_u {void* val; TYPE_4__ f; } ;
struct TYPE_16__ {int /*<<< orphan*/  cfgreg_base; } ;
union cfgreg_base_u {scalar_t__ val; TYPE_7__ f; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct w100fb_par {TYPE_1__* mach; } ;
struct w100_gpio_regs {int init_data1; int init_data2; int gpio_dir1; int gpio_oe1; int gpio_dir2; int gpio_oe2; } ;
struct TYPE_10__ {struct w100_gpio_regs* gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  W100_CFG_BASE ; 
 int W100_REG_BASE ; 
 int WRAP_BUF_BASE_VALUE ; 
 int WRAP_BUF_TOP_VALUE ; 
 scalar_t__ cfgCPU_DEFAULTS ; 
 scalar_t__ cfgINTF_CNTL ; 
 scalar_t__ cfgREG_BASE ; 
 scalar_t__ defCFGREG_BASE ; 
 scalar_t__ defCIF_IO ; 
 scalar_t__ defCPU_DEFAULTS ; 
 scalar_t__ defINTF_CNTL ; 
 scalar_t__ defWRAP_START_DIR ; 
 scalar_t__ defWRAP_TOP_DIR ; 
 scalar_t__ mmCFGREG_BASE ; 
 scalar_t__ mmCIF_CNTL ; 
 scalar_t__ mmCIF_IO ; 
 scalar_t__ mmCIF_READ_DBG ; 
 scalar_t__ mmCIF_WRITE_DBG ; 
 scalar_t__ mmDISP_DEBUG2 ; 
 scalar_t__ mmGPIO_CNTL1 ; 
 scalar_t__ mmGPIO_CNTL2 ; 
 scalar_t__ mmGPIO_CNTL3 ; 
 scalar_t__ mmGPIO_CNTL4 ; 
 scalar_t__ mmGPIO_DATA ; 
 scalar_t__ mmGPIO_DATA2 ; 
 scalar_t__ mmRBBM_CNTL ; 
 scalar_t__ mmSCRATCH_UMSK ; 
 scalar_t__ mmWRAP_START_DIR ; 
 scalar_t__ mmWRAP_TOP_DIR ; 
 void* readl (scalar_t__) ; 
 scalar_t__ remapped_base ; 
 scalar_t__ remapped_regs ; 
 int /*<<< orphan*/  w100_soft_reset () ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void w100_hw_init(struct w100fb_par *par)
{
	u32 temp32;
	union cif_cntl_u cif_cntl;
	union intf_cntl_u intf_cntl;
	union cfgreg_base_u cfgreg_base;
	union wrap_top_dir_u wrap_top_dir;
	union cif_read_dbg_u cif_read_dbg;
	union cpu_defaults_u cpu_default;
	union cif_write_dbg_u cif_write_dbg;
	union wrap_start_dir_u wrap_start_dir;
	union cif_io_u cif_io;
	struct w100_gpio_regs *gpio = par->mach->gpio;

	w100_soft_reset();

	/* This is what the fpga_init code does on reset. May be wrong
	   but there is little info available */
	writel(0x31, remapped_regs + mmSCRATCH_UMSK);
	for (temp32 = 0; temp32 < 10000; temp32++)
		readl(remapped_regs + mmSCRATCH_UMSK);
	writel(0x30, remapped_regs + mmSCRATCH_UMSK);

	/* Set up CIF */
	cif_io.val = defCIF_IO;
	writel((u32)(cif_io.val), remapped_regs + mmCIF_IO);

	cif_write_dbg.val = readl(remapped_regs + mmCIF_WRITE_DBG);
	cif_write_dbg.f.dis_packer_ful_during_rbbm_timeout = 0;
	cif_write_dbg.f.en_dword_split_to_rbbm = 1;
	cif_write_dbg.f.dis_timeout_during_rbbm = 1;
	writel((u32) (cif_write_dbg.val), remapped_regs + mmCIF_WRITE_DBG);

	cif_read_dbg.val = readl(remapped_regs + mmCIF_READ_DBG);
	cif_read_dbg.f.dis_rd_same_byte_to_trig_fetch = 1;
	writel((u32) (cif_read_dbg.val), remapped_regs + mmCIF_READ_DBG);

	cif_cntl.val = readl(remapped_regs + mmCIF_CNTL);
	cif_cntl.f.dis_system_bits = 1;
	cif_cntl.f.dis_mr = 1;
	cif_cntl.f.en_wait_to_compensate_dq_prop_dly = 0;
	cif_cntl.f.intb_oe = 1;
	cif_cntl.f.interrupt_active_high = 1;
	writel((u32) (cif_cntl.val), remapped_regs + mmCIF_CNTL);

	/* Setup cfgINTF_CNTL and cfgCPU defaults */
	intf_cntl.val = defINTF_CNTL;
	intf_cntl.f.ad_inc_a = 1;
	intf_cntl.f.ad_inc_b = 1;
	intf_cntl.f.rd_data_rdy_a = 0;
	intf_cntl.f.rd_data_rdy_b = 0;
	writeb((u8) (intf_cntl.val), remapped_base + cfgINTF_CNTL);

	cpu_default.val = defCPU_DEFAULTS;
	cpu_default.f.access_ind_addr_a = 1;
	cpu_default.f.access_ind_addr_b = 1;
	cpu_default.f.access_scratch_reg = 1;
	cpu_default.f.transition_size = 0;
	writeb((u8) (cpu_default.val), remapped_base + cfgCPU_DEFAULTS);

	/* set up the apertures */
	writeb((u8) (W100_REG_BASE >> 16), remapped_base + cfgREG_BASE);

	cfgreg_base.val = defCFGREG_BASE;
	cfgreg_base.f.cfgreg_base = W100_CFG_BASE;
	writel((u32) (cfgreg_base.val), remapped_regs + mmCFGREG_BASE);

	wrap_start_dir.val = defWRAP_START_DIR;
	wrap_start_dir.f.start_addr = WRAP_BUF_BASE_VALUE >> 1;
	writel((u32) (wrap_start_dir.val), remapped_regs + mmWRAP_START_DIR);

	wrap_top_dir.val = defWRAP_TOP_DIR;
	wrap_top_dir.f.top_addr = WRAP_BUF_TOP_VALUE >> 1;
	writel((u32) (wrap_top_dir.val), remapped_regs + mmWRAP_TOP_DIR);

	writel((u32) 0x2440, remapped_regs + mmRBBM_CNTL);

	/* Set the hardware to 565 colour */
	temp32 = readl(remapped_regs + mmDISP_DEBUG2);
	temp32 &= 0xff7fffff;
	temp32 |= 0x00800000;
	writel(temp32, remapped_regs + mmDISP_DEBUG2);

	/* Initialise the GPIO lines */
	if (gpio) {
		writel(gpio->init_data1, remapped_regs + mmGPIO_DATA);
		writel(gpio->init_data2, remapped_regs + mmGPIO_DATA2);
		writel(gpio->gpio_dir1,  remapped_regs + mmGPIO_CNTL1);
		writel(gpio->gpio_oe1,   remapped_regs + mmGPIO_CNTL2);
		writel(gpio->gpio_dir2,  remapped_regs + mmGPIO_CNTL3);
		writel(gpio->gpio_oe2,   remapped_regs + mmGPIO_CNTL4);
	}
}