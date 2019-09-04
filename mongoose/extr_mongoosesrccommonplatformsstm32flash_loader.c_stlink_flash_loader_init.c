#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  stlink_t ;
struct TYPE_3__ {scalar_t__ loader_addr; scalar_t__ buf_addr; } ;
typedef  TYPE_1__ flash_loader_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int stlink_flash_loader_write_to_sram (int /*<<< orphan*/ *,scalar_t__*,size_t*) ; 

int stlink_flash_loader_init(stlink_t *sl, flash_loader_t *fl) {
  size_t size;

  /* allocate the loader in sram */
  if (stlink_flash_loader_write_to_sram(sl, &fl->loader_addr, &size) == -1) {
    printf("Failed to write flash loader to sram!\n");
    return -1;
  }

  /* allocate a one page buffer in sram right after loader */
  fl->buf_addr = fl->loader_addr + (uint32_t) size;

  return 0;
}