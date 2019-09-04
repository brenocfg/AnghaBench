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
struct TYPE_2__ {int /*<<< orphan*/  writemask; } ;
struct shader_reg {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_print_relarg (struct shader_reg const*) ; 
 int /*<<< orphan*/  debug_print_writemask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_regname (struct shader_reg const*) ; 
 char const* wine_dbg_sprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *debug_print_dstreg(const struct shader_reg *reg)
{
    return wine_dbg_sprintf("%s%s%s", get_regname(reg),
            debug_print_relarg(reg),
            debug_print_writemask(reg->u.writemask));
}