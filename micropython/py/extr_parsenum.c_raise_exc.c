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
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_4__ {int /*<<< orphan*/ * type; } ;
typedef  TYPE_1__ mp_obj_base_t ;
struct TYPE_5__ {int /*<<< orphan*/  tok_line; int /*<<< orphan*/  source_name; } ;
typedef  TYPE_2__ mp_lexer_t ;

/* Variables and functions */
 scalar_t__ MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_QSTRnull ; 
 int /*<<< orphan*/  mp_obj_exception_add_traceback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_type_SyntaxError ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 

void raise_exc(mp_obj_t exc, mp_lexer_t *lex) {
    // if lex!=NULL then the parser called us and we need to convert the
    // exception's type from ValueError to SyntaxError and add traceback info
    if (lex != NULL) {
        ((mp_obj_base_t*)MP_OBJ_TO_PTR(exc))->type = &mp_type_SyntaxError;
        mp_obj_exception_add_traceback(exc, lex->source_name, lex->tok_line, MP_QSTRnull);
    }
    nlr_raise(exc);
}