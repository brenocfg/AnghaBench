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
typedef  int D3DSHADER_PARAM_REGISTER_TYPE ;

/* Variables and functions */
 int D3DSP_REGNUM_MASK ; 
 int D3DSP_REGTYPE_MASK ; 
 int D3DSP_REGTYPE_MASK2 ; 
 int D3DSP_REGTYPE_SHIFT ; 
 int D3DSP_REGTYPE_SHIFT2 ; 

__attribute__((used)) static DWORD d3dsp_register( D3DSHADER_PARAM_REGISTER_TYPE type, DWORD num )
{
    return ((type << D3DSP_REGTYPE_SHIFT) & D3DSP_REGTYPE_MASK) |
           ((type << D3DSP_REGTYPE_SHIFT2) & D3DSP_REGTYPE_MASK2) |
           (num & D3DSP_REGNUM_MASK); /* No shift */
}