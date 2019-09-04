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
typedef  int uint8_t ;
struct arm_gdb_reg_file {scalar_t__ fpscr; int /*<<< orphan*/  d; int /*<<< orphan*/  cpsr; int /*<<< orphan*/  pc; int /*<<< orphan*/  lr; int /*<<< orphan*/  sp; int /*<<< orphan*/ * r; } ;
struct arm_exc_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mgos_cd_printf (char*,...) ; 
 int /*<<< orphan*/  mgos_dev_system_restart () ; 
 int /*<<< orphan*/  portDISABLE_INTERRUPTS () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void arm_exc_handler_bottom(uint8_t isr_no, struct arm_exc_frame *ef,
                            struct arm_gdb_reg_file *rf) {
  char buf[8];
  const char *name;
  (void) ef;
  portDISABLE_INTERRUPTS();
  switch (isr_no) {
    case 0:
      name = "ThreadMode";
      break;

    case 1:
    case 7:
    case 8:
    case 9:
    case 10:
    case 13:
      name = "Reserved";
      break;

    case 2:
      name = "NMI";
      break;
    case 3:
      name = "HardFault";
      break;
    case 4:
      name = "MemManage";
      break;
    case 5:
      name = "BusFault";
      break;
    case 6:
      name = "UsageFault";
      break;
    case 11:
      name = "SVCall";
      break;
    case 12:
      name = "ReservedDebug";
      break;
    case 14:
      name = "PendSV";
      break;
    case 15:
      name = "SysTick";
      break;
    default: {
#ifndef MGOS_BOOT_BUILD
      sprintf(buf, "IRQ%u", isr_no - 16);
#endif
      name = buf;
    }
  }
  mgos_cd_printf("\n\n--- Exception %u (%s) ---\n", isr_no, name);
  if (rf != NULL) {
    mgos_cd_printf(
        "  R%d:  0x%08lx  R%d:  0x%08lx  R%d:  0x%08lx  R%d:  0x%08lx\n", 0,
        rf->r[0], 1, rf->r[1], 2, rf->r[2], 3, rf->r[3]);
    mgos_cd_printf(
        "  R%d:  0x%08lx  R%d:  0x%08lx  R%d:  0x%08lx  R%d:  0x%08lx\n", 4,
        rf->r[4], 5, rf->r[5], 6, rf->r[6], 7, rf->r[7]);
    mgos_cd_printf("  R8:  0x%08lx  R9:  0x%08lx  R10: 0x%08lx  R11: 0x%08lx\n",
                   rf->r[8], rf->r[9], rf->r[10], rf->r[11]);
    mgos_cd_printf("  R12: 0x%08lx  SP:  0x%08lx  LR:  0x%08lx  PC:  0x%08lx\n",
                   rf->r[12], rf->sp, rf->lr, rf->pc);
    mgos_cd_printf("  PSR: 0x%08lx\n", rf->cpsr);
  }
  memset(rf->d, 0, sizeof(rf->d));
#if ARM_HAVE_FPU && !defined(MGOS_BOOT_BUILD)
  rf->fpscr = ef->fpscr;
  memcpy((uint8_t *) rf->d, ef->s, sizeof(ef->s));
  print_fpu_regs((uint32_t *) rf->d, 0, ARRAY_SIZE(ef->s));
  save_s16_s31(ef->s);
  memcpy(((uint8_t *) rf->d) + sizeof(ef->s), ef->s, sizeof(ef->s));
  print_fpu_regs((uint32_t *) (((uint8_t *) rf->d) + sizeof(ef->s)), 16,
                 ARRAY_SIZE(ef->s));
  mgos_cd_putc('\n');
  mgos_cd_printf("FPSCR: 0x%08lx\n", rf->fpscr);
#else
  rf->fpscr = 0;
#endif
#if MGOS_ENABLE_CORE_DUMP
  mgos_cd_emit_header();
  mgos_cd_emit_section(MGOS_CORE_DUMP_SECTION_REGS, rf, sizeof(*rf));
  mgos_cd_emit_section("SRAM", (void *) SRAM_BASE_ADDR, SRAM_SIZE);
  mgos_cd_emit_footer();
#endif
#ifdef MGOS_HALT_ON_EXCEPTION
  mgos_cd_printf("Halting\n");
  while (1) {
    mgos_wdt_feed();
  }
#else
  mgos_cd_printf("Rebooting\n");
  mgos_dev_system_restart();
#endif
}