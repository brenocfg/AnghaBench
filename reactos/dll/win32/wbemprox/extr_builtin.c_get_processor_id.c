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
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  do_cpuid (int,unsigned int*) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,unsigned int,unsigned int) ; 

__attribute__((used)) static void get_processor_id( WCHAR *processor_id )
{
    static const WCHAR fmtW[] = {'%','0','8','X','%','0','8','X',0};
    unsigned int regs[4] = {0, 0, 0, 0};

    do_cpuid( 1, regs );
    sprintfW( processor_id, fmtW, regs[3], regs[0] );
}