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
typedef  int /*<<< orphan*/  vstr_t ;
typedef  int /*<<< orphan*/  qstr ;
typedef  int /*<<< orphan*/  mp_print_t ;
typedef  int /*<<< orphan*/  mp_obj_type_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_6__ {int /*<<< orphan*/  hash; scalar_t__ data; } ;
typedef  TYPE_1__ mp_obj_str_t ;
struct TYPE_7__ {int /*<<< orphan*/  len; scalar_t__ buf; } ;
typedef  TYPE_2__ mp_buffer_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_STR_DATA_LEN (int /*<<< orphan*/  const,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_STR_HASH (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_BUFFER_READ ; 
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_OBJ_NEW_QSTR (int /*<<< orphan*/ ) ; 
 TYPE_1__* MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_QSTR_ ; 
 int /*<<< orphan*/  MP_QSTRnull ; 
 int /*<<< orphan*/  PRINT_STR ; 
 int /*<<< orphan*/  mp_arg_check_num (size_t,size_t,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mp_arg_error_unimpl_kw () ; 
 int /*<<< orphan*/  mp_get_buffer_raise (int /*<<< orphan*/  const,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_is_type (int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_obj_new_str (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_new_str_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_new_str_from_vstr (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_obj_print_helper (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_raise_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_type_UnicodeError ; 
 int /*<<< orphan*/  mp_type_bytes ; 
 int /*<<< orphan*/  qstr_compute_hash (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qstr_find_strn (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ str_data ; 
 int /*<<< orphan*/  str_hash ; 
 int /*<<< orphan*/  str_len ; 
 int /*<<< orphan*/  utf8_check (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vstr_init_print (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

mp_obj_t mp_obj_str_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
#if MICROPY_CPYTHON_COMPAT
    if (n_kw != 0) {
        mp_arg_error_unimpl_kw();
    }
#endif

    mp_arg_check_num(n_args, n_kw, 0, 3, false);

    switch (n_args) {
        case 0:
            return MP_OBJ_NEW_QSTR(MP_QSTR_);

        case 1: {
            vstr_t vstr;
            mp_print_t print;
            vstr_init_print(&vstr, 16, &print);
            mp_obj_print_helper(&print, args[0], PRINT_STR);
            return mp_obj_new_str_from_vstr(type, &vstr);
        }

        default: // 2 or 3 args
            // TODO: validate 2nd/3rd args
            if (mp_obj_is_type(args[0], &mp_type_bytes)) {
                GET_STR_DATA_LEN(args[0], str_data, str_len);
                GET_STR_HASH(args[0], str_hash);
                if (str_hash == 0) {
                    str_hash = qstr_compute_hash(str_data, str_len);
                }
                #if MICROPY_PY_BUILTINS_STR_UNICODE_CHECK
                if (!utf8_check(str_data, str_len)) {
                    mp_raise_msg(&mp_type_UnicodeError, NULL);
                }
                #endif

                // Check if a qstr with this data already exists
                qstr q = qstr_find_strn((const char*)str_data, str_len);
                if (q != MP_QSTRnull) {
                    return MP_OBJ_NEW_QSTR(q);
                }

                mp_obj_str_t *o = MP_OBJ_TO_PTR(mp_obj_new_str_copy(type, NULL, str_len));
                o->data = str_data;
                o->hash = str_hash;
                return MP_OBJ_FROM_PTR(o);
            } else {
                mp_buffer_info_t bufinfo;
                mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_READ);
                #if MICROPY_PY_BUILTINS_STR_UNICODE_CHECK
                if (!utf8_check(bufinfo.buf, bufinfo.len)) {
                    mp_raise_msg(&mp_type_UnicodeError, NULL);
                }
                #endif
                return mp_obj_new_str(bufinfo.buf, bufinfo.len);
            }
    }
}