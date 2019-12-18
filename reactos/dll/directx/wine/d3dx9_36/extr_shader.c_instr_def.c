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
struct instr_info {int dummy; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int D3DSP_REGNUM_MASK ; 
 int sprintf (char*,char*,int,double,double,double,double) ; 

__attribute__((used)) static int instr_def(const struct instr_info *info, DWORD **ptr, char *buffer, BOOL ps)
{
    int len = sprintf(buffer, "    def c%d, %g, %g, %g, %g\n", *(*ptr+1) & D3DSP_REGNUM_MASK,
                      (double)*(float*)(*ptr+2), (double)*(float*)(*ptr+3),
                      (double)*(float*)(*ptr+4), (double)*(float*)(*ptr+5));
    *ptr += 6;
    return len;
}