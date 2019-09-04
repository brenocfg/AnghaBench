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
struct YYLTYPE {int /*<<< orphan*/  first_column; int /*<<< orphan*/  first_line; } ;
struct TYPE_2__ {int /*<<< orphan*/  source_file; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  HLSL_LEVEL_ERROR ; 
 int HLSL_MODIFIER_COLUMN_MAJOR ; 
 int HLSL_MODIFIER_ROW_MAJOR ; 
 int /*<<< orphan*/  debug_modifiers (int) ; 
 TYPE_1__ hlsl_ctx ; 
 int /*<<< orphan*/  hlsl_report_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static DWORD add_modifier(DWORD modifiers, DWORD mod, const struct YYLTYPE *loc)
{
    if (modifiers & mod)
    {
        hlsl_report_message(hlsl_ctx.source_file, loc->first_line, loc->first_column, HLSL_LEVEL_ERROR,
                "modifier '%s' already specified", debug_modifiers(mod));
        return modifiers;
    }
    if (mod & (HLSL_MODIFIER_ROW_MAJOR | HLSL_MODIFIER_COLUMN_MAJOR)
            && modifiers & (HLSL_MODIFIER_ROW_MAJOR | HLSL_MODIFIER_COLUMN_MAJOR))
    {
        hlsl_report_message(hlsl_ctx.source_file, loc->first_line, loc->first_column, HLSL_LEVEL_ERROR,
                "more than one matrix majority keyword");
        return modifiers;
    }
    return modifiers | mod;
}