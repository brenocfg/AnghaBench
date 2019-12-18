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

/* Variables and functions */
 int /*<<< orphan*/  SystemInit () ; 
 unsigned int __bss_section_table_end ; 
 unsigned int __data_section_table ; 
 unsigned int __data_section_table_end ; 
 int /*<<< orphan*/  __libc_init_array () ; 
 int /*<<< orphan*/  __main () ; 
 int /*<<< orphan*/  bss_init (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  data_init (unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ g_pfnVectors ; 
 int /*<<< orphan*/  main () ; 

__attribute__ ((section(".after_vectors")))
void
ResetISR(void) {

    //
    // Copy the data sections from flash to SRAM.
    //
    unsigned int LoadAddr, ExeAddr, SectionLen;
    unsigned int *SectionTableAddr;

    // Load base address of Global Section Table
    SectionTableAddr = &__data_section_table;

    // Copy the data sections from flash to SRAM.
    while (SectionTableAddr < &__data_section_table_end) {
        LoadAddr = *SectionTableAddr++;
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        data_init(LoadAddr, ExeAddr, SectionLen);
    }
    // At this point, SectionTableAddr = &__bss_section_table;
    // Zero fill the bss segment
    while (SectionTableAddr < &__bss_section_table_end) {
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        bss_init(ExeAddr, SectionLen);
    }

#if defined (__VFP_FP__) && !defined (__SOFTFP__)
/*
 * Code to enable the Cortex-M4 FPU only included
 * if appropriate build options have been selected.
 * Code taken from Section 7.1, Cortex-M4 TRM (DDI0439C)
 */  
    // Read CPACR (located at address 0xE000ED88)
    // Set bits 20-23 to enable CP10 and CP11 coprocessors
    // Write back the modified value to the CPACR
    asm volatile ("LDR.W R0, =0xE000ED88\n\t"
                  "LDR R1, [R0]\n\t"
                  "ORR R1, R1, #(0xF << 20)\n\t"
                  "STR R1, [R0]");  
#endif // (__VFP_FP__) && !(__SOFTFP__)

    // Check to see if we are running the code from a non-zero
    // address (eg RAM, external flash), in which case we need
    // to modify the VTOR register to tell the CPU that the
    // vector table is located at a non-0x0 address.

    // Note that we do not use the CMSIS register access mechanism,
    // as there is no guarantee that the project has been configured
    // to use CMSIS.
    unsigned int * pSCB_VTOR = (unsigned int *) 0xE000ED08;
    if ((unsigned int *)g_pfnVectors!=(unsigned int *) 0x00000000) {
        // CMSIS : SCB->VTOR = <address of vector table>
        *pSCB_VTOR = (unsigned int)g_pfnVectors;
    }

#if defined (__USE_CMSIS) || defined (__USE_LPCOPEN)
    SystemInit();
#endif

#if defined (__cplusplus)
    //
    // Call C++ library initialisation
    //
    __libc_init_array();
#endif

#if defined (__REDLIB__)
    // Call the Redlib library, which in turn calls main()
    __main() ;
#else
    main();
#endif

    //
    // main() shouldn't return, but if it does, we'll just enter an infinite loop 
    //
    while (1) {
        ;
    }
}