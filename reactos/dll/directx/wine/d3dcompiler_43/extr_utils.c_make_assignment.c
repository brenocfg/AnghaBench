#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hlsl_type {scalar_t__ type; int dimx; int dimy; int /*<<< orphan*/  base_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  col; int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
struct hlsl_ir_node {scalar_t__ type; TYPE_2__ loc; struct hlsl_type* data_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  var; } ;
struct hlsl_ir_deref {scalar_t__ type; int /*<<< orphan*/  node; TYPE_1__ v; } ;
struct hlsl_ir_assignment {int writemask; struct hlsl_ir_node node; struct hlsl_ir_node* rhs; struct hlsl_ir_node* lhs; } ;
typedef  enum parse_assign_op { ____Placeholder_parse_assign_op } parse_assign_op ;
typedef  enum hlsl_type_class { ____Placeholder_hlsl_type_class } hlsl_type_class ;
typedef  enum hlsl_ir_expr_op { ____Placeholder_hlsl_ir_expr_op } hlsl_ir_expr_op ;
typedef  int DWORD ;

/* Variables and functions */
 int ASSIGN_OP_ASSIGN ; 
 int BWRITERSP_WRITEMASK_ALL ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ HLSL_CLASS_LAST_NUMERIC ; 
 scalar_t__ HLSL_CLASS_MATRIX ; 
 int HLSL_CLASS_SCALAR ; 
 scalar_t__ HLSL_IR_ASSIGNMENT ; 
 scalar_t__ HLSL_IR_DEREF ; 
 scalar_t__ HLSL_IR_DEREF_VAR ; 
 int /*<<< orphan*/  HLSL_LEVEL_ERROR ; 
 int /*<<< orphan*/  HLSL_LEVEL_WARNING ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  compare_hlsl_types (struct hlsl_type*,struct hlsl_type*) ; 
 struct hlsl_ir_assignment* d3dcompiler_alloc (int) ; 
 int /*<<< orphan*/  d3dcompiler_free (struct hlsl_ir_assignment*) ; 
 int /*<<< orphan*/  debug_hlsl_type (struct hlsl_type*) ; 
 struct hlsl_ir_deref* deref_from_node (struct hlsl_ir_node*) ; 
 int /*<<< orphan*/  free_instr (struct hlsl_ir_node*) ; 
 int /*<<< orphan*/  hlsl_report_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  implicit_compatible_data_types (struct hlsl_type*,struct hlsl_type*) ; 
 struct hlsl_ir_node* implicit_conversion (struct hlsl_ir_node*,struct hlsl_type*,TYPE_2__*) ; 
 struct hlsl_ir_node* new_binary_expr (int,int /*<<< orphan*/ *,struct hlsl_ir_node*,TYPE_2__) ; 
 struct hlsl_type* new_hlsl_type (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,unsigned int,int) ; 
 struct hlsl_ir_deref* new_var_deref (int /*<<< orphan*/ ) ; 
 int op_from_assignment (int) ; 

struct hlsl_ir_node *make_assignment(struct hlsl_ir_node *left, enum parse_assign_op assign_op,
        DWORD writemask, struct hlsl_ir_node *right)
{
    struct hlsl_ir_assignment *assign = d3dcompiler_alloc(sizeof(*assign));
    struct hlsl_type *type;
    struct hlsl_ir_node *lhs, *rhs;

    if (!assign)
    {
        ERR("Out of memory\n");
        return NULL;
    }

    TRACE("Creating proper assignment expression.\n");
    rhs = right;
    if (writemask == BWRITERSP_WRITEMASK_ALL)
        type = left->data_type;
    else
    {
        unsigned int dimx = 0;
        DWORD bitmask;
        enum hlsl_type_class type_class;

        if (left->data_type->type > HLSL_CLASS_LAST_NUMERIC)
        {
            hlsl_report_message(left->loc.file, left->loc.line, left->loc.col, HLSL_LEVEL_ERROR,
                    "writemask on a non scalar/vector/matrix type");
            d3dcompiler_free(assign);
            return NULL;
        }
        bitmask = writemask & ((1 << left->data_type->dimx) - 1);
        while (bitmask)
        {
            if (bitmask & 1)
                dimx++;
            bitmask >>= 1;
        }
        if (left->data_type->type == HLSL_CLASS_MATRIX)
            FIXME("Assignments with writemasks and matrices on lhs are not supported yet.\n");
        if (dimx == 1)
            type_class = HLSL_CLASS_SCALAR;
        else
            type_class = left->data_type->type;
        type = new_hlsl_type(NULL, type_class, left->data_type->base_type, dimx, 1);
    }
    assign->node.type = HLSL_IR_ASSIGNMENT;
    assign->node.loc = left->loc;
    assign->node.data_type = type;
    assign->writemask = writemask;
    FIXME("Check for casts in the lhs.\n");

    lhs = left;
    /* FIXME: check for invalid writemasks on the lhs. */

    if (!compare_hlsl_types(type, rhs->data_type))
    {
        struct hlsl_ir_node *converted_rhs;

        if (!implicit_compatible_data_types(rhs->data_type, type))
        {
            hlsl_report_message(rhs->loc.file, rhs->loc.line, rhs->loc.col, HLSL_LEVEL_ERROR,
                    "can't implicitly convert %s to %s",
                    debug_hlsl_type(rhs->data_type), debug_hlsl_type(type));
            free_instr(lhs);
            free_instr(rhs);
            d3dcompiler_free(assign);
            return NULL;
        }
        if (lhs->data_type->dimx * lhs->data_type->dimy < rhs->data_type->dimx * rhs->data_type->dimy)
            hlsl_report_message(rhs->loc.file, rhs->loc.line, rhs->loc.col, HLSL_LEVEL_WARNING,
                    "implicit truncation of vector type");

        converted_rhs = implicit_conversion(rhs, type, &rhs->loc);
        if (!converted_rhs)
        {
            ERR("Couldn't implicitly convert expression to %s.\n", debug_hlsl_type(type));
            free_instr(lhs);
            free_instr(rhs);
            d3dcompiler_free(assign);
            return NULL;
        }
        rhs = converted_rhs;
    }

    assign->lhs = lhs;
    if (assign_op != ASSIGN_OP_ASSIGN)
    {
        enum hlsl_ir_expr_op op = op_from_assignment(assign_op);
        struct hlsl_ir_node *expr;

        if (lhs->type != HLSL_IR_DEREF || deref_from_node(lhs)->type != HLSL_IR_DEREF_VAR)
        {
            FIXME("LHS expression not supported in compound assignments yet.\n");
            assign->rhs = rhs;
        }
        else
        {
            struct hlsl_ir_deref *lhs_deref = deref_from_node(lhs), *new_deref;

            TRACE("Adding an expression for the compound assignment.\n");
            new_deref = new_var_deref(lhs_deref->v.var);
            expr = new_binary_expr(op, &new_deref->node, rhs, left->loc);
            assign->rhs = expr;
        }
    }
    else
        assign->rhs = rhs;

    return &assign->node;
}