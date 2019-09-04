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
struct TYPE_2__ {int /*<<< orphan*/  swizzle; } ;
struct shader_reg {int srcmod; TYPE_1__ u; } ;

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
 int /*<<< orphan*/  debug_print_relarg (struct shader_reg const*) ; 
 int /*<<< orphan*/  debug_print_swizzle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_regname (struct shader_reg const*) ; 
 char const* wine_dbg_sprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *debug_print_srcreg(const struct shader_reg *reg)
{
    switch (reg->srcmod)
    {
        case BWRITERSPSM_NONE:
            return wine_dbg_sprintf("%s%s%s", get_regname(reg),
                    debug_print_relarg(reg),
                    debug_print_swizzle(reg->u.swizzle));
        case BWRITERSPSM_NEG:
            return wine_dbg_sprintf("-%s%s%s", get_regname(reg),
                    debug_print_relarg(reg),
                    debug_print_swizzle(reg->u.swizzle));
        case BWRITERSPSM_BIAS:
            return wine_dbg_sprintf("%s%s_bias%s", get_regname(reg),
                    debug_print_relarg(reg),
                    debug_print_swizzle(reg->u.swizzle));
        case BWRITERSPSM_BIASNEG:
            return wine_dbg_sprintf("-%s%s_bias%s", get_regname(reg),
                    debug_print_relarg(reg),
                    debug_print_swizzle(reg->u.swizzle));
        case BWRITERSPSM_SIGN:
            return wine_dbg_sprintf("%s%s_bx2%s", get_regname(reg),
                    debug_print_relarg(reg),
                    debug_print_swizzle(reg->u.swizzle));
        case BWRITERSPSM_SIGNNEG:
            return wine_dbg_sprintf("-%s%s_bx2%s", get_regname(reg),
                    debug_print_relarg(reg),
                    debug_print_swizzle(reg->u.swizzle));
        case BWRITERSPSM_COMP:
            return wine_dbg_sprintf("1 - %s%s%s", get_regname(reg),
                    debug_print_relarg(reg),
                    debug_print_swizzle(reg->u.swizzle));
        case BWRITERSPSM_X2:
            return wine_dbg_sprintf("%s%s_x2%s", get_regname(reg),
                    debug_print_relarg(reg),
                    debug_print_swizzle(reg->u.swizzle));
        case BWRITERSPSM_X2NEG:
            return wine_dbg_sprintf("-%s%s_x2%s", get_regname(reg),
                    debug_print_relarg(reg),
                    debug_print_swizzle(reg->u.swizzle));
        case BWRITERSPSM_DZ:
            return wine_dbg_sprintf("%s%s_dz%s", get_regname(reg),
                    debug_print_relarg(reg),
                    debug_print_swizzle(reg->u.swizzle));
        case BWRITERSPSM_DW:
            return wine_dbg_sprintf("%s%s_dw%s", get_regname(reg),
                    debug_print_relarg(reg),
                    debug_print_swizzle(reg->u.swizzle));
        case BWRITERSPSM_ABS:
            return wine_dbg_sprintf("%s%s_abs%s", get_regname(reg),
                    debug_print_relarg(reg),
                    debug_print_swizzle(reg->u.swizzle));
        case BWRITERSPSM_ABSNEG:
            return wine_dbg_sprintf("-%s%s_abs%s", get_regname(reg),
                    debug_print_relarg(reg),
                    debug_print_swizzle(reg->u.swizzle));
        case BWRITERSPSM_NOT:
            return wine_dbg_sprintf("!%s%s%s", get_regname(reg),
                    debug_print_relarg(reg),
                    debug_print_swizzle(reg->u.swizzle));
    }
    return "Unknown modifier";
}