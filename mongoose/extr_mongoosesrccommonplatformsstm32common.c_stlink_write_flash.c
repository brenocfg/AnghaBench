#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int stm32_addr_t ;
struct TYPE_14__ {int flash_base; int flash_size; int flash_pgsz; } ;
typedef  TYPE_1__ stlink_t ;
typedef  int /*<<< orphan*/  flash_loader_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lock_flash (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_flash_cr_pg (TYPE_1__*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ stlink_calculate_pagesize (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stlink_core_id (TYPE_1__*) ; 
 int stlink_erase_flash_page (TYPE_1__*,int) ; 
 int stlink_flash_loader_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int stlink_flash_loader_run (TYPE_1__*,int /*<<< orphan*/ *,int,scalar_t__*,size_t) ; 
 int stlink_target_voltage (TYPE_1__*) ; 
 int stlink_verify_write_flash (TYPE_1__*,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  unlock_flash_if (TYPE_1__*) ; 
 int /*<<< orphan*/  write_flash_cr_psiz (TYPE_1__*,int) ; 

int stlink_write_flash(stlink_t *sl, stm32_addr_t addr, uint8_t *base,
                       uint32_t len, uint8_t eraseonly) {
  size_t off;
  flash_loader_t fl;
  printf("Writing %d (%#x) bytes to stm32 address: %u (%#x)\n", len, len, addr,
         addr);
  /* check addr range is inside the flash */
  stlink_calculate_pagesize(sl, addr);
  if (addr < sl->flash_base) {
    printf("addr too low %#x < %#x\n", addr, sl->flash_base);
    return -1;
  } else if ((addr + len) < addr) {
    printf("addr overruns\n");
    return -1;
  } else if ((addr + len) > (sl->flash_base + sl->flash_size)) {
    printf("addr too high\n");
    return -1;
  } else if (addr & 1) {
    printf("unaligned addr 0x%x\n", addr);
    return -1;
  } else if (len & 1) {
    printf("unaligned len 0x%x -- padding with zero\n", len);
    len += 1;
  } else if (addr & (sl->flash_pgsz - 1)) {
    printf("addr not a multiple of pagesize, not supported\n");
    return -1;
  }

  // Make sure we've loaded the context with the chip details
  stlink_core_id(sl);
  /* erase each page */
  int page_count = 0;
  for (off = 0; off < len;
       off += stlink_calculate_pagesize(sl, addr + (uint32_t) off)) {
    fprintf(stdout, "Erasing flash page at addr 0x%08X\n", (int) (addr + off));
    /* addr must be an addr inside the page */
    if (stlink_erase_flash_page(sl, addr + (uint32_t) off) == -1) {
      printf("Failed to erase_flash_page(%#zx) == -1\n", addr + off);
      return -1;
    }
    page_count++;
  }

  if (eraseonly) return 0;

  /* flash loader initialization */
  if (stlink_flash_loader_init(sl, &fl) == -1) {
    printf("stlink_flash_loader_init() == -1\n");
    return -1;
  }

  /* First unlock the cr */
  unlock_flash_if(sl);

  /* TODO: Check that Voltage range is 2.7 - 3.6 V */
  /* set parallelisim to 32 bit*/
  int voltage = stlink_target_voltage(sl);
  if (voltage == -1) {
    printf("Failed to read Target voltage\n");
    return voltage;
  } else if (voltage > 2700) {
    write_flash_cr_psiz(sl, 2);
  } else {
    printf(
        "Target voltage (%d mV) too low for 32-bit flash, using 8-bit "
        "flash writes\n",
        voltage);
    write_flash_cr_psiz(sl, 0);
  }

  /* set programming mode */
  set_flash_cr_pg(sl);

  for (off = 0; off < len;) {
    size_t size = len - off > 0x8000 ? 0x8000 : len - off;
    printf("Writing %d bytes at 0x%08X\n", (int) size,
           (int) (addr + (uint32_t) off));
    if (stlink_flash_loader_run(sl, &fl, addr + (uint32_t) off, base + off,
                                size) == -1) {
      printf("stlink_flash_loader_run(%#zx) failed! == -1\n", addr + off);
      return -1;
    }
    off += size;
  }

  /* Relock flash */
  lock_flash(sl);

  return stlink_verify_write_flash(sl, addr, base, len);
}