#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct stlink_chipid_params {int flash_size_reg; int /*<<< orphan*/  bootrom_size; int /*<<< orphan*/  bootrom_base; int /*<<< orphan*/  sram_size; int /*<<< orphan*/  flash_pagesize; } ;
struct TYPE_6__ {int chip_id; int flash_size; int /*<<< orphan*/  sys_size; int /*<<< orphan*/  sys_base; int /*<<< orphan*/  sram_size; int /*<<< orphan*/  flash_pgsz; int /*<<< orphan*/  sram_base; int /*<<< orphan*/  flash_base; } ;
typedef  TYPE_1__ stlink_t ;

/* Variables and functions */
 struct stlink_chipid_params F7_params ; 
 int STLINK_CHIPID_STM32_F7 ; 
 int /*<<< orphan*/  STM32_FLASH_BASE ; 
 int /*<<< orphan*/  STM32_SRAM_BASE ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stlink_chip_id (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  stlink_core_id (TYPE_1__*) ; 
 int /*<<< orphan*/  stlink_read_debug32 (TYPE_1__*,int,int*) ; 

int stlink_load_device_params(stlink_t *sl) {
  const struct stlink_chipid_params *params = &F7_params;
  stlink_core_id(sl);
  uint32_t chip_id;
  uint32_t flash_size;

  stlink_chip_id(sl, &chip_id);
  sl->chip_id = chip_id & 0xfff;
  /* Fix chip_id for F4 rev A errata , Read CPU ID, as CoreID is the same for
   * F2/F4*/
  if (sl->chip_id == 0x411) {
    uint32_t cpuid;
    stlink_read_debug32(sl, 0xE000ED00, &cpuid);
    if ((cpuid & 0xfff0) == 0xc240) sl->chip_id = 0x413;
  }

  if (sl->chip_id != STLINK_CHIPID_STM32_F7) {
    printf("unsupported chip id! %d\n", chip_id);
    return -1;
  }

  // These are fixed...
  sl->flash_base = STM32_FLASH_BASE;
  sl->sram_base = STM32_SRAM_BASE;
  stlink_read_debug32(sl, (params->flash_size_reg) & ~3, &flash_size);
  if (params->flash_size_reg & 2) flash_size = flash_size >> 16;
  flash_size = flash_size & 0xffff;

  sl->flash_size = flash_size * 1024;
  sl->flash_pgsz = params->flash_pagesize;
  sl->sram_size = params->sram_size;
  sl->sys_base = params->bootrom_base;
  sl->sys_size = params->bootrom_size;

  return 0;
}