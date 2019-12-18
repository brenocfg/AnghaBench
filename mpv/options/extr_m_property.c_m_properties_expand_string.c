#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct m_property {int dummy; } ;
struct TYPE_13__ {int len; char* start; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (int /*<<< orphan*/ *,char*,int,char) ; 
 int /*<<< orphan*/  append_str (char**,int*,TYPE_1__) ; 
 TYPE_1__ bstr0 (char const*) ; 
 TYPE_1__ bstr_cut (TYPE_1__,int) ; 
 int bstr_eatstart0 (TYPE_1__*,char*) ; 
 scalar_t__ bstr_find0 (TYPE_1__,char*) ; 
 TYPE_1__ bstr_splice (TYPE_1__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bstr_startswith0 (TYPE_1__,char*) ; 
 int bstrcspn (TYPE_1__,char*) ; 
 int expand_property (struct m_property const*,char**,int*,TYPE_1__,int,void*) ; 

char *m_properties_expand_string(const struct m_property *prop_list,
                                 const char *str0, void *ctx)
{
    char *ret = NULL;
    int ret_len = 0;
    bool skip = false;
    int level = 0, skip_level = 0;
    bstr str = bstr0(str0);

    while (str.len) {
        if (level > 0 && bstr_eatstart0(&str, "}")) {
            if (skip && level <= skip_level)
                skip = false;
            level--;
        } else if (bstr_startswith0(str, "${") && bstr_find0(str, "}") >= 0) {
            str = bstr_cut(str, 2);
            level++;

            // Assume ":" and "}" can't be part of the property name
            // => if ":" comes before "}", it must be for the fallback
            int term_pos = bstrcspn(str, ":}");
            bstr name = bstr_splice(str, 0, term_pos < 0 ? str.len : term_pos);
            str = bstr_cut(str, term_pos);
            bool have_fallback = bstr_eatstart0(&str, ":");

            if (!skip) {
                skip = expand_property(prop_list, &ret, &ret_len, name,
                                       have_fallback, ctx);
                if (skip)
                    skip_level = level;
            }
        } else if (level == 0 && bstr_eatstart0(&str, "$>")) {
            append_str(&ret, &ret_len, str);
            break;
        } else {
            char c;

            // Other combinations, e.g. "$x", are added verbatim
            if (bstr_eatstart0(&str, "$$")) {
                c = '$';
            } else if (bstr_eatstart0(&str, "$}")) {
                c = '}';
            } else {
                c = str.start[0];
                str = bstr_cut(str, 1);
            }

            if (!skip)
                MP_TARRAY_APPEND(NULL, ret, ret_len, c);
        }
    }

    MP_TARRAY_APPEND(NULL, ret, ret_len, '\0');
    return ret;
}