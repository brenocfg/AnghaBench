#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int qstr ;
struct TYPE_3__ {int /*<<< orphan*/  ret_val; } ;
typedef  TYPE_1__ nlr_buf_t ;
typedef  int /*<<< orphan*/  mp_parse_tree_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int /*<<< orphan*/  mp_lexer_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_PARSE_FILE_INPUT ; 
 int /*<<< orphan*/  mp_call_function_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_compile (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * mp_lexer_new_from_str_len (int,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlr_pop () ; 
 scalar_t__ nlr_push (TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

mp_obj_t execute_from_str(const char *str) {
    nlr_buf_t nlr;
    if (nlr_push(&nlr) == 0) {
        qstr src_name = 1/*MP_QSTR_*/;
        mp_lexer_t *lex = mp_lexer_new_from_str_len(src_name, str, strlen(str), false);
        mp_parse_tree_t pt = mp_parse(lex, MP_PARSE_FILE_INPUT);
        mp_obj_t module_fun = mp_compile(&pt, src_name, false);
        mp_call_function_0(module_fun);
        nlr_pop();
        return 0;
    } else {
        // uncaught exception
        return (mp_obj_t)nlr.ret_val;
    }
}