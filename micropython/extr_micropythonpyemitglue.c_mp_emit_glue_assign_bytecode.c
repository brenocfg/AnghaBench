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
typedef  int /*<<< orphan*/  mp_uint_t ;
struct TYPE_3__ {int /*<<< orphan*/  const* const_table; int /*<<< orphan*/  const* fun_data; int /*<<< orphan*/  scope_flags; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ mp_raw_code_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  MP_CODE_BYTECODE ; 

void mp_emit_glue_assign_bytecode(mp_raw_code_t *rc, const byte *code,
    #if MICROPY_PERSISTENT_CODE_SAVE || MICROPY_DEBUG_PRINTERS
    size_t len,
    #endif
    const mp_uint_t *const_table,
    #if MICROPY_PERSISTENT_CODE_SAVE
    uint16_t n_obj, uint16_t n_raw_code,
    #endif
    mp_uint_t scope_flags) {

    rc->kind = MP_CODE_BYTECODE;
    rc->scope_flags = scope_flags;
    rc->fun_data = code;
    rc->const_table = const_table;
    #if MICROPY_PERSISTENT_CODE_SAVE
    rc->fun_data_len = len;
    rc->n_obj = n_obj;
    rc->n_raw_code = n_raw_code;
    #endif

#ifdef DEBUG_PRINT
    #if !MICROPY_DEBUG_PRINTERS
    const size_t len = 0;
    #endif
    DEBUG_printf("assign byte code: code=%p len=" UINT_FMT " flags=%x\n", code, len, (uint)scope_flags);
#endif
#if MICROPY_DEBUG_PRINTERS
    if (mp_verbose_flag >= 2) {
        mp_bytecode_print(rc, code, len, const_table);
    }
#endif
}