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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SystemInit () ; 
 int /*<<< orphan*/  _ebss ; 
 int /*<<< orphan*/  _edata ; 
 int /*<<< orphan*/  _sbss ; 
 int /*<<< orphan*/  _sdata ; 
 int /*<<< orphan*/  _sidata ; 
 int /*<<< orphan*/  _start () ; 

void Reset_Handler(void) {
    uint32_t * p_src  = &_sidata;
    uint32_t * p_dest = &_sdata;

    while (p_dest < &_edata) {
      *p_dest++ = *p_src++;
    }

    uint32_t * p_bss     = &_sbss;
    uint32_t * p_bss_end = &_ebss;
    while (p_bss < p_bss_end) {
        *p_bss++ = 0ul;
    }

    SystemInit();
    _start();
}