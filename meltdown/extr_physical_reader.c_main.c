#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int physical_offset; } ;
typedef  TYPE_1__ libkdump_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libkdump_cleanup () ; 
 TYPE_1__ libkdump_get_autoconfig () ; 
 int /*<<< orphan*/  libkdump_init (TYPE_1__) ; 
 size_t libkdump_phys_to_virt (size_t) ; 
 int libkdump_read (size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 void* strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
  size_t phys;
  if (argc < 2) {
    printf("Usage: %s <physical address> [<direct physical map>]\n", argv[0]);
    return 0;
  }

  phys = strtoull(argv[1], NULL, 0);

  libkdump_config_t config;
  config = libkdump_get_autoconfig();
  if (argc > 2) {
    config.physical_offset = strtoull(argv[2], NULL, 0);
  }

  libkdump_init(config);

  size_t vaddr = libkdump_phys_to_virt(phys);

  printf("\x1b[32;1m[+]\x1b[0m Physical address       : \x1b[33;1m0x%zx\x1b[0m\n", phys);
  printf("\x1b[32;1m[+]\x1b[0m Physical offset        : \x1b[33;1m0x%zx\x1b[0m\n", config.physical_offset);
  printf("\x1b[32;1m[+]\x1b[0m Reading virtual address: \x1b[33;1m0x%zx\x1b[0m\n\n", vaddr);

  while (1) {
    int value = libkdump_read(vaddr);
    printf("%c", value);
    fflush(stdout);
    vaddr++;
  }

  libkdump_cleanup();

  return 0;
}