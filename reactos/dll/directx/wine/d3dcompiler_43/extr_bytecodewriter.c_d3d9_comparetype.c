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
#define  BWRITER_COMPARISON_EQ 133 
#define  BWRITER_COMPARISON_GE 132 
#define  BWRITER_COMPARISON_GT 131 
#define  BWRITER_COMPARISON_LE 130 
#define  BWRITER_COMPARISON_LT 129 
#define  BWRITER_COMPARISON_NE 128 
 int D3DSPC_EQ ; 
 int D3DSPC_GE ; 
 int D3DSPC_GT ; 
 int D3DSPC_LE ; 
 int D3DSPC_LT ; 
 int D3DSPC_NE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 

__attribute__((used)) static DWORD d3d9_comparetype(DWORD asmshader_comparetype)
{
    switch (asmshader_comparetype)
    {
        case BWRITER_COMPARISON_GT:     return D3DSPC_GT;
        case BWRITER_COMPARISON_EQ:     return D3DSPC_EQ;
        case BWRITER_COMPARISON_GE:     return D3DSPC_GE;
        case BWRITER_COMPARISON_LT:     return D3DSPC_LT;
        case BWRITER_COMPARISON_NE:     return D3DSPC_NE;
        case BWRITER_COMPARISON_LE:     return D3DSPC_LE;
        default:
            FIXME("Unexpected BWRITER_COMPARISON type %#x.\n", asmshader_comparetype);
            return 0;
    }
}