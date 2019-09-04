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
#define  BWRITERSPSM_ABS 141 
#define  BWRITERSPSM_ABSNEG 140 
#define  BWRITERSPSM_BIAS 139 
#define  BWRITERSPSM_BIASNEG 138 
#define  BWRITERSPSM_COMP 137 
#define  BWRITERSPSM_DW 136 
#define  BWRITERSPSM_DZ 135 
#define  BWRITERSPSM_NEG 134 
#define  BWRITERSPSM_NONE 133 
#define  BWRITERSPSM_NOT 132 
#define  BWRITERSPSM_SIGN 131 
#define  BWRITERSPSM_SIGNNEG 130 
#define  BWRITERSPSM_X2 129 
#define  BWRITERSPSM_X2NEG 128 
 int D3DSPSM_ABS ; 
 int D3DSPSM_ABSNEG ; 
 int D3DSPSM_BIAS ; 
 int D3DSPSM_BIASNEG ; 
 int D3DSPSM_COMP ; 
 int D3DSPSM_DW ; 
 int D3DSPSM_DZ ; 
 int D3DSPSM_NEG ; 
 int D3DSPSM_NONE ; 
 int D3DSPSM_NOT ; 
 int D3DSPSM_SIGN ; 
 int D3DSPSM_SIGNNEG ; 
 int D3DSPSM_X2 ; 
 int D3DSPSM_X2NEG ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 

__attribute__((used)) static DWORD d3d9_srcmod(DWORD bwriter_srcmod)
{
    switch (bwriter_srcmod)
    {
        case BWRITERSPSM_NONE:       return D3DSPSM_NONE;
        case BWRITERSPSM_NEG:        return D3DSPSM_NEG;
        case BWRITERSPSM_BIAS:       return D3DSPSM_BIAS;
        case BWRITERSPSM_BIASNEG:    return D3DSPSM_BIASNEG;
        case BWRITERSPSM_SIGN:       return D3DSPSM_SIGN;
        case BWRITERSPSM_SIGNNEG:    return D3DSPSM_SIGNNEG;
        case BWRITERSPSM_COMP:       return D3DSPSM_COMP;
        case BWRITERSPSM_X2:         return D3DSPSM_X2;
        case BWRITERSPSM_X2NEG:      return D3DSPSM_X2NEG;
        case BWRITERSPSM_DZ:         return D3DSPSM_DZ;
        case BWRITERSPSM_DW:         return D3DSPSM_DW;
        case BWRITERSPSM_ABS:        return D3DSPSM_ABS;
        case BWRITERSPSM_ABSNEG:     return D3DSPSM_ABSNEG;
        case BWRITERSPSM_NOT:        return D3DSPSM_NOT;
        default:
            FIXME("Unhandled BWRITERSPSM token %#x.\n", bwriter_srcmod);
            return 0;
    }
}