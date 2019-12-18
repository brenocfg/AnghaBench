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
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3DSPSM_ABS 140 
#define  WINED3DSPSM_ABSNEG 139 
#define  WINED3DSPSM_BIAS 138 
#define  WINED3DSPSM_BIASNEG 137 
#define  WINED3DSPSM_COMP 136 
#define  WINED3DSPSM_DW 135 
#define  WINED3DSPSM_DZ 134 
#define  WINED3DSPSM_NEG 133 
#define  WINED3DSPSM_NONE 132 
#define  WINED3DSPSM_SIGN 131 
#define  WINED3DSPSM_SIGNNEG 130 
#define  WINED3DSPSM_X2 129 
#define  WINED3DSPSM_X2NEG 128 

__attribute__((used)) static DWORD negate_modifiers(DWORD mod, char *extra_char)
{
    *extra_char = ' ';
    switch(mod)
    {
        case WINED3DSPSM_NONE:      return WINED3DSPSM_NEG;
        case WINED3DSPSM_NEG:       return WINED3DSPSM_NONE;
        case WINED3DSPSM_BIAS:      return WINED3DSPSM_BIASNEG;
        case WINED3DSPSM_BIASNEG:   return WINED3DSPSM_BIAS;
        case WINED3DSPSM_SIGN:      return WINED3DSPSM_SIGNNEG;
        case WINED3DSPSM_SIGNNEG:   return WINED3DSPSM_SIGN;
        case WINED3DSPSM_COMP:      *extra_char = '-'; return WINED3DSPSM_COMP;
        case WINED3DSPSM_X2:        return WINED3DSPSM_X2NEG;
        case WINED3DSPSM_X2NEG:     return WINED3DSPSM_X2;
        case WINED3DSPSM_DZ:        *extra_char = '-'; return WINED3DSPSM_DZ;
        case WINED3DSPSM_DW:        *extra_char = '-'; return WINED3DSPSM_DW;
        case WINED3DSPSM_ABS:       return WINED3DSPSM_ABSNEG;
        case WINED3DSPSM_ABSNEG:    return WINED3DSPSM_ABS;
    }
    FIXME("Unknown modifier %u\n", mod);
    return mod;
}