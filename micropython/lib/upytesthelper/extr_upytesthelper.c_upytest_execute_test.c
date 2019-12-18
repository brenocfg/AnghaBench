#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qstr ;
struct TYPE_6__ {int /*<<< orphan*/  ret_val; } ;
typedef  TYPE_1__ nlr_buf_t ;
typedef  int /*<<< orphan*/  mp_parse_tree_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_7__ {int /*<<< orphan*/  source_name; } ;
typedef  TYPE_2__ mp_lexer_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_PARSE_FILE_INPUT ; 
 int /*<<< orphan*/  MP_QSTR__lt_stdin_gt_ ; 
 int /*<<< orphan*/  gc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_end ; 
 int /*<<< orphan*/  heap_start ; 
 int /*<<< orphan*/  mp_call_function_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_compile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_deinit () ; 
 int /*<<< orphan*/  mp_init () ; 
 TYPE_2__* mp_lexer_new_from_str_len (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_subclass_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_obj_list_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_print_exception (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_parse (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_plat_print ; 
 int /*<<< orphan*/  mp_sys_argv ; 
 int /*<<< orphan*/  mp_sys_path ; 
 int /*<<< orphan*/  mp_type_SystemExit ; 
 int /*<<< orphan*/  nlr_pop () ; 
 scalar_t__ nlr_push (TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  tinytest_set_test_failed_ () ; 
 int /*<<< orphan*/  tinytest_set_test_skipped_ () ; 
 int /*<<< orphan*/  tt_abort_msg (char*) ; 
 scalar_t__ upytest_is_failed () ; 

void upytest_execute_test(const char *src) {
    // To provide clean room for each test, interpreter and heap are
    // reinitialized before running each.
    gc_init(heap_start, heap_end);
    mp_init();
    mp_obj_list_init(mp_sys_path, 0);
    mp_obj_list_init(mp_sys_argv, 0);

    nlr_buf_t nlr;
    if (nlr_push(&nlr) == 0) {
        mp_lexer_t *lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, src, strlen(src), 0);
        qstr source_name = lex->source_name;
        mp_parse_tree_t parse_tree = mp_parse(lex, MP_PARSE_FILE_INPUT);
        mp_obj_t module_fun = mp_compile(&parse_tree, source_name, false);
        mp_call_function_0(module_fun);
        nlr_pop();
    } else {
        mp_obj_t exc = (mp_obj_t)nlr.ret_val;
        if (mp_obj_is_subclass_fast(mp_obj_get_type(exc), &mp_type_SystemExit)) {
            // Assume that sys.exit() is called to skip the test.
            // TODO: That can be always true, we should set up convention to
            // use specific exit code as skip indicator.
            tinytest_set_test_skipped_();
            goto end;
        }
        mp_obj_print_exception(&mp_plat_print, exc);
        tt_abort_msg("Uncaught exception\n");
    }

    if (upytest_is_failed()) {
        tinytest_set_test_failed_();
    }

end:
    mp_deinit();
}