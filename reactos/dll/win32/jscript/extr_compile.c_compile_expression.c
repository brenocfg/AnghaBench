#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unary_expression_t ;
typedef  int /*<<< orphan*/  property_value_expression_t ;
typedef  int /*<<< orphan*/  member_expression_t ;
struct TYPE_5__ {int /*<<< orphan*/  literal; } ;
typedef  TYPE_1__ literal_expression_t ;
struct TYPE_6__ {int /*<<< orphan*/  identifier; } ;
typedef  TYPE_2__ identifier_expression_t ;
typedef  int /*<<< orphan*/  function_expression_t ;
struct TYPE_7__ {int type; } ;
typedef  TYPE_3__ expression_t ;
typedef  int /*<<< orphan*/  conditional_expression_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
typedef  int /*<<< orphan*/  call_expression_t ;
typedef  int /*<<< orphan*/  binary_expression_t ;
typedef  int /*<<< orphan*/  array_literal_expression_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_UNREACHABLE ; 
#define  EXPR_ADD 185 
#define  EXPR_AND 184 
#define  EXPR_ARRAY 183 
#define  EXPR_ARRAYLIT 182 
#define  EXPR_ASSIGN 181 
#define  EXPR_ASSIGNADD 180 
#define  EXPR_ASSIGNAND 179 
#define  EXPR_ASSIGNDIV 178 
#define  EXPR_ASSIGNLSHIFT 177 
#define  EXPR_ASSIGNMOD 176 
#define  EXPR_ASSIGNMUL 175 
#define  EXPR_ASSIGNOR 174 
#define  EXPR_ASSIGNRRSHIFT 173 
#define  EXPR_ASSIGNRSHIFT 172 
#define  EXPR_ASSIGNSUB 171 
#define  EXPR_ASSIGNXOR 170 
#define  EXPR_BAND 169 
#define  EXPR_BITNEG 168 
#define  EXPR_BOR 167 
#define  EXPR_BXOR 166 
#define  EXPR_CALL 165 
#define  EXPR_COMMA 164 
#define  EXPR_COND 163 
#define  EXPR_DELETE 162 
#define  EXPR_DIV 161 
#define  EXPR_EQ 160 
#define  EXPR_EQEQ 159 
#define  EXPR_FUNC 158 
#define  EXPR_GREATER 157 
#define  EXPR_GREATEREQ 156 
#define  EXPR_IDENT 155 
#define  EXPR_IN 154 
#define  EXPR_INSTANCEOF 153 
#define  EXPR_LESS 152 
#define  EXPR_LESSEQ 151 
#define  EXPR_LITERAL 150 
#define  EXPR_LOGNEG 149 
#define  EXPR_LSHIFT 148 
#define  EXPR_MEMBER 147 
#define  EXPR_MINUS 146 
#define  EXPR_MOD 145 
#define  EXPR_MUL 144 
#define  EXPR_NEW 143 
#define  EXPR_NOTEQ 142 
#define  EXPR_NOTEQEQ 141 
#define  EXPR_OR 140 
#define  EXPR_PLUS 139 
#define  EXPR_POSTDEC 138 
#define  EXPR_POSTINC 137 
#define  EXPR_PREDEC 136 
#define  EXPR_PREINC 135 
#define  EXPR_PROPVAL 134 
#define  EXPR_RRSHIFT 133 
#define  EXPR_RSHIFT 132 
#define  EXPR_SUB 131 
#define  EXPR_THIS 130 
#define  EXPR_TYPEOF 129 
#define  EXPR_VOID 128 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_LAST ; 
 int /*<<< orphan*/  OP_add ; 
 int /*<<< orphan*/  OP_and ; 
 int /*<<< orphan*/  OP_array ; 
 int /*<<< orphan*/  OP_bneg ; 
 int /*<<< orphan*/  OP_cnd_nz ; 
 int /*<<< orphan*/  OP_cnd_z ; 
 int /*<<< orphan*/  OP_div ; 
 int /*<<< orphan*/  OP_eq ; 
 int /*<<< orphan*/  OP_eq2 ; 
 int /*<<< orphan*/  OP_gt ; 
 int /*<<< orphan*/  OP_gteq ; 
 int /*<<< orphan*/  OP_in ; 
 int /*<<< orphan*/  OP_instanceof ; 
 int /*<<< orphan*/  OP_lshift ; 
 int /*<<< orphan*/  OP_lt ; 
 int /*<<< orphan*/  OP_lteq ; 
 int /*<<< orphan*/  OP_minus ; 
 int /*<<< orphan*/  OP_mod ; 
 int /*<<< orphan*/  OP_mul ; 
 int /*<<< orphan*/  OP_neg ; 
 int /*<<< orphan*/  OP_neq ; 
 int /*<<< orphan*/  OP_neq2 ; 
 int /*<<< orphan*/  OP_or ; 
 int /*<<< orphan*/  OP_pop ; 
 int /*<<< orphan*/  OP_postinc ; 
 int /*<<< orphan*/  OP_preinc ; 
 int /*<<< orphan*/  OP_rshift ; 
 int /*<<< orphan*/  OP_rshift2 ; 
 int /*<<< orphan*/  OP_sub ; 
 int /*<<< orphan*/  OP_this ; 
 int /*<<< orphan*/  OP_tonum ; 
 int /*<<< orphan*/  OP_void ; 
 int /*<<< orphan*/  OP_xor ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  compile_array_literal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_assign_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_binary_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_call_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  compile_comma_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  compile_conditional_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_delete_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_function_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  compile_increment_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  compile_literal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_logical_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_member_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_new_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_object_literal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_typeof_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_unary_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_identifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT compile_expression(compiler_ctx_t *ctx, expression_t *expr, BOOL emit_ret)
{
    HRESULT hres;

    switch(expr->type) {
    case EXPR_ADD:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_add);
        break;
    case EXPR_AND:
        hres = compile_logical_expression(ctx, (binary_expression_t*)expr, OP_cnd_z);
        break;
    case EXPR_ARRAY:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_array);
        break;
    case EXPR_ARRAYLIT:
        hres = compile_array_literal(ctx, (array_literal_expression_t*)expr);
        break;
    case EXPR_ASSIGN:
        hres = compile_assign_expression(ctx, (binary_expression_t*)expr, OP_LAST);
        break;
    case EXPR_ASSIGNADD:
        hres = compile_assign_expression(ctx, (binary_expression_t*)expr, OP_add);
        break;
    case EXPR_ASSIGNAND:
        hres = compile_assign_expression(ctx, (binary_expression_t*)expr, OP_and);
        break;
    case EXPR_ASSIGNSUB:
        hres = compile_assign_expression(ctx, (binary_expression_t*)expr, OP_sub);
        break;
    case EXPR_ASSIGNMUL:
        hres = compile_assign_expression(ctx, (binary_expression_t*)expr, OP_mul);
        break;
    case EXPR_ASSIGNDIV:
        hres = compile_assign_expression(ctx, (binary_expression_t*)expr, OP_div);
        break;
    case EXPR_ASSIGNMOD:
        hres = compile_assign_expression(ctx, (binary_expression_t*)expr, OP_mod);
        break;
    case EXPR_ASSIGNOR:
        hres = compile_assign_expression(ctx, (binary_expression_t*)expr, OP_or);
        break;
    case EXPR_ASSIGNLSHIFT:
        hres = compile_assign_expression(ctx, (binary_expression_t*)expr, OP_lshift);
        break;
    case EXPR_ASSIGNRSHIFT:
        hres = compile_assign_expression(ctx, (binary_expression_t*)expr, OP_rshift);
        break;
    case EXPR_ASSIGNRRSHIFT:
        hres = compile_assign_expression(ctx, (binary_expression_t*)expr, OP_rshift2);
        break;
    case EXPR_ASSIGNXOR:
        hres = compile_assign_expression(ctx, (binary_expression_t*)expr, OP_xor);
        break;
    case EXPR_BAND:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_and);
        break;
    case EXPR_BITNEG:
        hres = compile_unary_expression(ctx, (unary_expression_t*)expr, OP_bneg);
        break;
    case EXPR_BOR:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_or);
        break;
    case EXPR_CALL:
        return compile_call_expression(ctx, (call_expression_t*)expr, emit_ret);
    case EXPR_COMMA:
        return compile_comma_expression(ctx, (binary_expression_t*)expr, emit_ret);
    case EXPR_COND:
        hres = compile_conditional_expression(ctx, (conditional_expression_t*)expr);
        break;
    case EXPR_DELETE:
        hres = compile_delete_expression(ctx, (unary_expression_t*)expr);
        break;
    case EXPR_DIV:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_div);
        break;
    case EXPR_EQ:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_eq);
        break;
    case EXPR_EQEQ:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_eq2);
        break;
    case EXPR_FUNC:
        return compile_function_expression(ctx, (function_expression_t*)expr, emit_ret);
    case EXPR_GREATER:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_gt);
        break;
    case EXPR_GREATEREQ:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_gteq);
        break;
    case EXPR_IDENT:
        hres = emit_identifier(ctx, ((identifier_expression_t*)expr)->identifier);
        break;
    case EXPR_IN:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_in);
        break;
    case EXPR_INSTANCEOF:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_instanceof);
        break;
    case EXPR_LESS:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_lt);
        break;
    case EXPR_LESSEQ:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_lteq);
        break;
    case EXPR_LITERAL:
        hres = compile_literal(ctx, ((literal_expression_t*)expr)->literal);
        break;
    case EXPR_LOGNEG:
        hres = compile_unary_expression(ctx, (unary_expression_t*)expr, OP_neg);
        break;
    case EXPR_LSHIFT:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_lshift);
        break;
    case EXPR_MEMBER:
        hres = compile_member_expression(ctx, (member_expression_t*)expr);
        break;
    case EXPR_MINUS:
        hres = compile_unary_expression(ctx, (unary_expression_t*)expr, OP_minus);
        break;
    case EXPR_MOD:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_mod);
        break;
    case EXPR_MUL:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_mul);
        break;
    case EXPR_NEW:
        hres = compile_new_expression(ctx, (call_expression_t*)expr);
        break;
    case EXPR_NOTEQ:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_neq);
        break;
    case EXPR_NOTEQEQ:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_neq2);
        break;
    case EXPR_OR:
        hres = compile_logical_expression(ctx, (binary_expression_t*)expr, OP_cnd_nz);
        break;
    case EXPR_PLUS:
        hres = compile_unary_expression(ctx, (unary_expression_t*)expr, OP_tonum);
        break;
    case EXPR_POSTDEC:
        hres = compile_increment_expression(ctx, (unary_expression_t*)expr, OP_postinc, -1);
        break;
    case EXPR_POSTINC:
        hres = compile_increment_expression(ctx, (unary_expression_t*)expr, OP_postinc, 1);
        break;
    case EXPR_PREDEC:
        hres = compile_increment_expression(ctx, (unary_expression_t*)expr, OP_preinc, -1);
        break;
    case EXPR_PREINC:
        hres = compile_increment_expression(ctx, (unary_expression_t*)expr, OP_preinc, 1);
        break;
    case EXPR_PROPVAL:
        hres = compile_object_literal(ctx, (property_value_expression_t*)expr);
        break;
    case EXPR_RSHIFT:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_rshift);
        break;
    case EXPR_RRSHIFT:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_rshift2);
        break;
    case EXPR_SUB:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_sub);
        break;
    case EXPR_THIS:
        return !emit_ret || push_instr(ctx, OP_this) ? S_OK : E_OUTOFMEMORY;
    case EXPR_TYPEOF:
        hres = compile_typeof_expression(ctx, (unary_expression_t*)expr);
        break;
    case EXPR_VOID:
        hres = compile_unary_expression(ctx, (unary_expression_t*)expr, OP_void);
        break;
    case EXPR_BXOR:
        hres = compile_binary_expression(ctx, (binary_expression_t*)expr, OP_xor);
        break;
    DEFAULT_UNREACHABLE;
    }

    if(FAILED(hres))
        return hres;

    return emit_ret ? S_OK : push_instr_uint(ctx, OP_pop, 1);
}