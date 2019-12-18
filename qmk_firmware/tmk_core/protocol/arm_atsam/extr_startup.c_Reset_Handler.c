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
typedef  int uint32_t ;
struct TYPE_2__ {int VTOR; int CPACR; } ;

/* Variables and functions */
 int BOOTLOADER_MAGIC ; 
 int* MAGIC_ADDR ; 
 TYPE_1__* SCB ; 
 int SCB_VTOR_TBLOFF_Msk ; 
 int /*<<< orphan*/  __DSB () ; 
 int /*<<< orphan*/  __ISB () ; 
 int /*<<< orphan*/  __libc_init_array () ; 
 int /*<<< orphan*/  __set_MSP (int) ; 
 int _erelocate ; 
 int _etext ; 
 int _ezero ; 
 int /*<<< orphan*/  _sfixed ; 
 int _srelocate ; 
 int _szero ; 
 int /*<<< orphan*/  main () ; 

void Reset_Handler(void) {
#ifdef KEYBOARD_massdrop_ctrl
    /* WARNING: This is only for CTRL bootloader release "v2.18Jun 22 2018 17:28:08" for bootloader_jump support */
    if (*MAGIC_ADDR == BOOTLOADER_MAGIC) {
        /* At this point, the bootloader's memory is initialized properly, so undo the jump to here, then jump back */
        *MAGIC_ADDR = 0x00000000;       /* Change value to prevent potential bootloader entrance loop */
        __set_MSP(0x20008818);          /* MSP according to bootloader */
        SCB->VTOR = 0x00000000;         /* Vector table back to bootloader's */
        asm("bx %0" ::"r"(0x00001267)); /* Jump past bootloader RCAUSE check using THUMB */
    }
#endif
    uint32_t *pSrc, *pDest;

    /* Initialize the relocate segment */
    pSrc  = &_etext;
    pDest = &_srelocate;

    if (pSrc != pDest) {
        for (; pDest < &_erelocate;) {
            *pDest++ = *pSrc++;
        }
    }

    /* Clear the zero segment */
    for (pDest = &_szero; pDest < &_ezero;) {
        *pDest++ = 0;
    }

    /* Set the vector table base address */
    pSrc      = (uint32_t *)&_sfixed;
    SCB->VTOR = ((uint32_t)pSrc & SCB_VTOR_TBLOFF_Msk);

#if __FPU_USED
    /* Enable FPU */
    SCB->CPACR |= (0xFu << 20);
    __DSB();
    __ISB();
#endif

    /* Initialize the C library */
    __libc_init_array();

    /* Branch to main function */
    main();

    /* Infinite loop */
    while (1)
        ;
}