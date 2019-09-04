#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  col; int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
struct TYPE_6__ {TYPE_4__ loc; TYPE_1__* data_type; } ;
struct hlsl_ir_var {int modifiers; int /*<<< orphan*/  name; TYPE_2__ node; scalar_t__ semantic; } ;
struct TYPE_7__ {scalar_t__ matrix_majority; int /*<<< orphan*/  cur_scope; } ;
struct TYPE_5__ {scalar_t__ type; } ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ HLSL_CLASS_MATRIX ; 
 int /*<<< orphan*/  HLSL_LEVEL_ERROR ; 
 int /*<<< orphan*/  HLSL_LEVEL_NOTE ; 
 int HLSL_MODIFIER_COLUMN_MAJOR ; 
 int HLSL_MODIFIER_ROW_MAJOR ; 
 scalar_t__ HLSL_ROW_MAJOR ; 
 int HLSL_STORAGE_EXTERN ; 
 int HLSL_STORAGE_GROUPSHARED ; 
 int HLSL_STORAGE_SHARED ; 
 int HLSL_STORAGE_UNIFORM ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 scalar_t__ add_declaration (int /*<<< orphan*/ ,struct hlsl_ir_var*,scalar_t__) ; 
 int /*<<< orphan*/  check_invalid_matrix_modifiers (int,TYPE_4__*) ; 
 int /*<<< orphan*/  debug_modifiers (int) ; 
 scalar_t__ find_function (int /*<<< orphan*/ ) ; 
 struct hlsl_ir_var* get_variable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ hlsl_ctx ; 
 int /*<<< orphan*/  hlsl_report_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static BOOL declare_variable(struct hlsl_ir_var *decl, BOOL local)
{
    BOOL ret;

    TRACE("Declaring variable %s.\n", decl->name);
    if (decl->node.data_type->type == HLSL_CLASS_MATRIX)
    {
        if (!(decl->modifiers & (HLSL_MODIFIER_ROW_MAJOR | HLSL_MODIFIER_COLUMN_MAJOR)))
        {
            decl->modifiers |= hlsl_ctx.matrix_majority == HLSL_ROW_MAJOR
                    ? HLSL_MODIFIER_ROW_MAJOR : HLSL_MODIFIER_COLUMN_MAJOR;
        }
    }
    else
        check_invalid_matrix_modifiers(decl->modifiers, &decl->node.loc);

    if (local)
    {
        DWORD invalid = decl->modifiers & (HLSL_STORAGE_EXTERN | HLSL_STORAGE_SHARED
                | HLSL_STORAGE_GROUPSHARED | HLSL_STORAGE_UNIFORM);
        if (invalid)
        {
            hlsl_report_message(decl->node.loc.file, decl->node.loc.line, decl->node.loc.col, HLSL_LEVEL_ERROR,
                    "modifier '%s' invalid for local variables", debug_modifiers(invalid));
        }
        if (decl->semantic)
        {
            hlsl_report_message(decl->node.loc.file, decl->node.loc.line, decl->node.loc.col, HLSL_LEVEL_ERROR,
                    "semantics are not allowed on local variables");
            return FALSE;
        }
    }
    else
    {
        if (find_function(decl->name))
        {
            hlsl_report_message(decl->node.loc.file, decl->node.loc.line, decl->node.loc.col, HLSL_LEVEL_ERROR,
                    "redefinition of '%s'", decl->name);
            return FALSE;
        }
    }
    ret = add_declaration(hlsl_ctx.cur_scope, decl, local);
    if (!ret)
    {
        struct hlsl_ir_var *old = get_variable(hlsl_ctx.cur_scope, decl->name);

        hlsl_report_message(decl->node.loc.file, decl->node.loc.line, decl->node.loc.col, HLSL_LEVEL_ERROR,
                "\"%s\" already declared", decl->name);
        hlsl_report_message(old->node.loc.file, old->node.loc.line, old->node.loc.col, HLSL_LEVEL_NOTE,
                "\"%s\" was previously declared here", old->name);
        return FALSE;
    }
    return TRUE;
}