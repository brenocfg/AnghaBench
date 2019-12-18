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
struct hlsl_ir_var {scalar_t__ semantic; int /*<<< orphan*/  name; int /*<<< orphan*/  data_type; scalar_t__ modifiers; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debug_hlsl_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_modifiers (scalar_t__) ; 
 int /*<<< orphan*/  debugstr_a (scalar_t__) ; 

__attribute__((used)) static void debug_dump_ir_var(const struct hlsl_ir_var *var)
{
    if (var->modifiers)
        TRACE("%s ", debug_modifiers(var->modifiers));
    TRACE("%s %s", debug_hlsl_type(var->data_type), var->name);
    if (var->semantic)
        TRACE(" : %s", debugstr_a(var->semantic));
}