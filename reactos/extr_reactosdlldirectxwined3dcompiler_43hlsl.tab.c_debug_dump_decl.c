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
struct hlsl_type {int dummy; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,unsigned int,...) ; 
 int /*<<< orphan*/  debug_hlsl_type (struct hlsl_type*) ; 
 int /*<<< orphan*/  debug_modifiers (scalar_t__) ; 

__attribute__((used)) static void debug_dump_decl(struct hlsl_type *type, DWORD modifiers, const char *declname, unsigned int line_no)
{
    TRACE("Line %u: ", line_no);
    if (modifiers)
        TRACE("%s ", debug_modifiers(modifiers));
    TRACE("%s %s;\n", debug_hlsl_type(type), declname);
}