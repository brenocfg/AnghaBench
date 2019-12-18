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
typedef  int DWORD ;

/* Variables and functions */
 int BWRITERSP_WRITEMASK_0 ; 
 int BWRITERSP_WRITEMASK_1 ; 
 int BWRITERSP_WRITEMASK_2 ; 
 int BWRITERSP_WRITEMASK_3 ; 
 int D3DSP_WRITEMASK_0 ; 
 int D3DSP_WRITEMASK_1 ; 
 int D3DSP_WRITEMASK_2 ; 
 int D3DSP_WRITEMASK_3 ; 

__attribute__((used)) static DWORD d3d9_writemask(DWORD bwriter_writemask)
{
    DWORD ret = 0;

    if (bwriter_writemask & BWRITERSP_WRITEMASK_0) ret |= D3DSP_WRITEMASK_0;
    if (bwriter_writemask & BWRITERSP_WRITEMASK_1) ret |= D3DSP_WRITEMASK_1;
    if (bwriter_writemask & BWRITERSP_WRITEMASK_2) ret |= D3DSP_WRITEMASK_2;
    if (bwriter_writemask & BWRITERSP_WRITEMASK_3) ret |= D3DSP_WRITEMASK_3;

    return ret;
}