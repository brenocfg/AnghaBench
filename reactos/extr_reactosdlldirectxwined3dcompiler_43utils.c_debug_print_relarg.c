#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct shader_reg {TYPE_2__* rel_reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  swizzle; } ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ regnum; TYPE_1__ u; } ;

/* Variables and functions */
 scalar_t__ BWRITERSPR_ADDR ; 
 scalar_t__ BWRITERSPR_LOOP ; 
 char* debug_print_swizzle (int /*<<< orphan*/ ) ; 
 char const* wine_dbg_sprintf (char*,char const*,...) ; 

__attribute__((used)) static const char *debug_print_relarg(const struct shader_reg *reg)
{
    const char *short_swizzle;
    if (!reg->rel_reg) return "";

    short_swizzle = debug_print_swizzle(reg->rel_reg->u.swizzle);

    if (reg->rel_reg->type == BWRITERSPR_ADDR)
        return wine_dbg_sprintf("[a%u%s]", reg->rel_reg->regnum, short_swizzle);
    else if(reg->rel_reg->type == BWRITERSPR_LOOP && reg->rel_reg->regnum == 0)
        return wine_dbg_sprintf("[aL%s]", short_swizzle);
    else
        return "Unexpected relative addressing argument";
}