#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* ptr; TYPE_1__* script; } ;
typedef  TYPE_2__ parser_ctx_t ;
typedef  int /*<<< orphan*/  ccval_t ;
struct TYPE_12__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_3__ cc_var_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 double NAN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ccval_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccval_num (double) ; 
 int /*<<< orphan*/  check_keyword (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 TYPE_3__* find_cc_var (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ iswdigit (char) ; 
 int /*<<< orphan*/  parse_cc_identifier (TYPE_2__*,int /*<<< orphan*/  const**,unsigned int*) ; 
 int /*<<< orphan*/  parse_numeric_literal (TYPE_2__*,double*) ; 
 int /*<<< orphan*/  skip_spaces (TYPE_2__*) ; 

int try_parse_ccval(parser_ctx_t *ctx, ccval_t *r)
{
    if(!skip_spaces(ctx))
        return -1;

    if(iswdigit(*ctx->ptr)) {
        double n;

        if(!parse_numeric_literal(ctx, &n))
            return -1;

        *r = ccval_num(n);
        return 1;
    }

    if(*ctx->ptr == '@') {
        const WCHAR *ident;
        unsigned ident_len;
        cc_var_t *cc_var;

        if(!parse_cc_identifier(ctx, &ident, &ident_len))
            return -1;

        cc_var = find_cc_var(ctx->script->cc, ident, ident_len);
        *r = cc_var ? cc_var->val : ccval_num(NAN);
        return 1;
    }

    if(!check_keyword(ctx, L"true", NULL)) {
        *r = ccval_bool(TRUE);
        return 1;
    }

    if(!check_keyword(ctx, L"false", NULL)) {
        *r = ccval_bool(FALSE);
        return 1;
    }

    return 0;
}