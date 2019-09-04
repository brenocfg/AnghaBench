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
typedef  int /*<<< orphan*/  mp_obj_type_t ;
typedef  scalar_t__ mp_obj_t ;
typedef  scalar_t__ mp_int_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  GET_STR_DATA_LEN (scalar_t__ const,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bad_implicit_conversion (scalar_t__) ; 
 int len ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char const*,size_t) ; 
 scalar_t__ mp_const_none ; 
 scalar_t__ mp_obj_get_int (scalar_t__ const) ; 
 int /*<<< orphan*/  const* mp_obj_get_type (scalar_t__ const) ; 
 int /*<<< orphan*/  mp_obj_list_append (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_new_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_obj_new_str_of_type (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 char* mp_obj_str_get_data (scalar_t__,size_t*) ; 
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 
 int /*<<< orphan*/  const* s ; 
 scalar_t__ unichar_isspace (int /*<<< orphan*/  const) ; 

mp_obj_t mp_obj_str_split(size_t n_args, const mp_obj_t *args) {
    const mp_obj_type_t *self_type = mp_obj_get_type(args[0]);
    mp_int_t splits = -1;
    mp_obj_t sep = mp_const_none;
    if (n_args > 1) {
        sep = args[1];
        if (n_args > 2) {
            splits = mp_obj_get_int(args[2]);
        }
    }

    mp_obj_t res = mp_obj_new_list(0, NULL);
    GET_STR_DATA_LEN(args[0], s, len);
    const byte *top = s + len;

    if (sep == mp_const_none) {
        // sep not given, so separate on whitespace

        // Initial whitespace is not counted as split, so we pre-do it
        while (s < top && unichar_isspace(*s)) s++;
        while (s < top && splits != 0) {
            const byte *start = s;
            while (s < top && !unichar_isspace(*s)) s++;
            mp_obj_list_append(res, mp_obj_new_str_of_type(self_type, start, s - start));
            if (s >= top) {
                break;
            }
            while (s < top && unichar_isspace(*s)) s++;
            if (splits > 0) {
                splits--;
            }
        }

        if (s < top) {
            mp_obj_list_append(res, mp_obj_new_str_of_type(self_type, s, top - s));
        }

    } else {
        // sep given
        if (mp_obj_get_type(sep) != self_type) {
            bad_implicit_conversion(sep);
        }

        size_t sep_len;
        const char *sep_str = mp_obj_str_get_data(sep, &sep_len);

        if (sep_len == 0) {
            mp_raise_ValueError("empty separator");
        }

        for (;;) {
            const byte *start = s;
            for (;;) {
                if (splits == 0 || s + sep_len > top) {
                    s = top;
                    break;
                } else if (memcmp(s, sep_str, sep_len) == 0) {
                    break;
                }
                s++;
            }
            mp_obj_list_append(res, mp_obj_new_str_of_type(self_type, start, s - start));
            if (s >= top) {
                break;
            }
            s += sep_len;
            if (splits > 0) {
                splits--;
            }
        }
    }

    return res;
}