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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  phys_size; int /*<<< orphan*/  phys_addr; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFS_RES_OK ; 
 TYPE_2__ fs ; 

__attribute__((used)) static sint32_t myspiffs_vfs_fscfg( uint32_t *phys_addr, uint32_t *phys_size ) {
  *phys_addr = fs.cfg.phys_addr;
  *phys_size = fs.cfg.phys_size;
  return VFS_RES_OK;
}