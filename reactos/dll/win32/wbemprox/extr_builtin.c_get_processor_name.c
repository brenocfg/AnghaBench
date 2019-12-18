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
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  do_cpuid (int,unsigned int*) ; 
 int /*<<< orphan*/  regs_to_str (unsigned int*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_processor_name( WCHAR *name )
{
    unsigned int regs[4] = {0, 0, 0, 0};

    do_cpuid( 0x80000000, regs );
    if (regs[0] >= 0x80000004)
    {
        do_cpuid( 0x80000002, regs );
        regs_to_str( regs, 16, name );
        do_cpuid( 0x80000003, regs );
        regs_to_str( regs, 16, name + 16 );
        do_cpuid( 0x80000004, regs );
        regs_to_str( regs, 16, name + 32 );
    }
}