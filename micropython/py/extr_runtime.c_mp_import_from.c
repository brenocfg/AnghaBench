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
typedef  size_t uint ;
typedef  int /*<<< orphan*/  qstr ;
typedef  scalar_t__ mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_printf (char*,scalar_t__,char const*) ; 
 int /*<<< orphan*/  MP_OBJ_NEW_SMALL_INT (int /*<<< orphan*/ ) ; 
 scalar_t__ MP_OBJ_NULL ; 
 int /*<<< orphan*/  MP_QSTR___name__ ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  mp_const_true ; 
 scalar_t__ mp_import_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_load_method_maybe (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 char* mp_local_alloc (size_t const) ; 
 int /*<<< orphan*/  mp_local_free (char*) ; 
 int /*<<< orphan*/  mp_obj_is_package (scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg_varg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* mp_obj_str_get_data (scalar_t__,size_t*) ; 
 int /*<<< orphan*/  mp_type_ImportError ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qstr_from_strn (char*,size_t const) ; 
 size_t qstr_len (int /*<<< orphan*/ ) ; 
 char const* qstr_str (int /*<<< orphan*/ ) ; 

mp_obj_t mp_import_from(mp_obj_t module, qstr name) {
    DEBUG_printf("import from %p %s\n", module, qstr_str(name));

    mp_obj_t dest[2];

    mp_load_method_maybe(module, name, dest);

    if (dest[1] != MP_OBJ_NULL) {
        // Hopefully we can't import bound method from an object
import_error:
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ImportError, "cannot import name %q", name));
    }

    if (dest[0] != MP_OBJ_NULL) {
        return dest[0];
    }

    #if MICROPY_ENABLE_EXTERNAL_IMPORT

    // See if it's a package, then can try FS import
    if (!mp_obj_is_package(module)) {
        goto import_error;
    }

    mp_load_method_maybe(module, MP_QSTR___name__, dest);
    size_t pkg_name_len;
    const char *pkg_name = mp_obj_str_get_data(dest[0], &pkg_name_len);

    const uint dot_name_len = pkg_name_len + 1 + qstr_len(name);
    char *dot_name = mp_local_alloc(dot_name_len);
    memcpy(dot_name, pkg_name, pkg_name_len);
    dot_name[pkg_name_len] = '.';
    memcpy(dot_name + pkg_name_len + 1, qstr_str(name), qstr_len(name));
    qstr dot_name_q = qstr_from_strn(dot_name, dot_name_len);
    mp_local_free(dot_name);

    // For fromlist, pass sentinel "non empty" value to force returning of leaf module
    return mp_import_name(dot_name_q, mp_const_true, MP_OBJ_NEW_SMALL_INT(0));

    #else

    // Package import not supported with external imports disabled
    goto import_error;

    #endif
}