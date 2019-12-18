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
struct TYPE_2__ {scalar_t__ physical_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*) ; 

size_t libkdump_phys_to_virt(size_t addr) {
  /* we are given full address (kernel or physical) here */
  if (addr + config.physical_offset < config.physical_offset)
    return addr;

#ifdef __x86_64__
  /* address given is bigger than identity mapping 64TB  */
  if (addr >= (64ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL)) {
    debug(ERROR, "phys_to_virt argument is > 64 TB\n");
    return -1ULL;
  }
#endif

  return addr + config.physical_offset;
}