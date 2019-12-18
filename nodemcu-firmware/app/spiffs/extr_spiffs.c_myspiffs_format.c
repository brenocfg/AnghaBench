#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  phys_size; } ;
struct TYPE_6__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NODE_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SPIFFS_format (TYPE_2__*) ; 
 int /*<<< orphan*/  SPIFFS_unmount (TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int erase_cnt ; 
 TYPE_2__ fs ; 
 int myspiffs_mount (int /*<<< orphan*/ ) ; 

int myspiffs_format( void )
{
  SPIFFS_unmount(&fs);
  myspiffs_mount(TRUE);
  SPIFFS_unmount(&fs);

  NODE_DBG("Formatting: size 0x%x, addr 0x%x\n", fs.cfg.phys_size, fs.cfg.phys_addr);
  erase_cnt = 0;
  int status = SPIFFS_format(&fs);
  erase_cnt = -1;

  return status < 0 ? 0 : myspiffs_mount(FALSE);
}