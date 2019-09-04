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
struct mp_log {int dummy; } ;
struct m_config {int dummy; } ;
struct TYPE_13__ {scalar_t__ len; scalar_t__ start; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 char const* BSTR_P (TYPE_1__) ; 
 int M_OPT_EXIT ; 
 int M_OPT_OUT_OF_RANGE ; 
 int M_OPT_UNKNOWN ; 
 TYPE_1__ bstr0 (char const*) ; 
 char* m_config_get_positional_option (struct m_config*,int) ; 
 scalar_t__ m_config_option_requires_param (struct m_config*,TYPE_1__) ; 
 int m_config_set_option_cli (struct m_config*,TYPE_1__,TYPE_1__,int) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static int get_obj_param(struct mp_log *log, bstr opt_name, bstr obj_name,
                         struct m_config *config, bstr name, bstr val,
                         int flags, bool nopos,
                         int *nold, bstr *out_name, bstr *out_val,
                         char *tmp, size_t tmp_size)
{
    int r;

    if (!config) {
        // Duplicates the logic below, but with unknown parameter types/names.
        if (val.start || nopos) {
            *out_name = name;
            *out_val = val;
        } else {
            val = name;
            // positional fields
            if (val.len == 0) { // Empty field, count it and go on
                (*nold)++;
                return 0;
            }
            // Positional naming convention for/followed by mp_set_avopts().
            snprintf(tmp, tmp_size, "@%d", *nold);
            *out_name = bstr0(tmp);
            *out_val = val;
            (*nold)++;
        }
        return 1;
    }

    // val.start != NULL => of the form name=val (not positional)
    // If it's just "name", and the associated option exists and is a flag,
    // don't accept it as positional argument.
    if (val.start || m_config_option_requires_param(config, name) == 0 || nopos) {
        r = m_config_set_option_cli(config, name, val, flags);
        if (r < 0) {
            if (r == M_OPT_UNKNOWN) {
                mp_err(log, "Option %.*s: %.*s doesn't have a %.*s parameter.\n",
                       BSTR_P(opt_name), BSTR_P(obj_name), BSTR_P(name));
                return M_OPT_UNKNOWN;
            }
            if (r != M_OPT_EXIT)
                mp_err(log, "Option %.*s: "
                       "Error while parsing %.*s parameter %.*s (%.*s)\n",
                       BSTR_P(opt_name), BSTR_P(obj_name), BSTR_P(name),
                       BSTR_P(val));
            return r;
        }
        *out_name = name;
        *out_val = val;
        return 1;
    } else {
        val = name;
        // positional fields
        if (val.len == 0) { // Empty field, count it and go on
            (*nold)++;
            return 0;
        }
        const char *opt = m_config_get_positional_option(config, *nold);
        if (!opt) {
            mp_err(log, "Option %.*s: %.*s has only %d "
                   "params, so you can't give more than %d unnamed params.\n",
                   BSTR_P(opt_name), BSTR_P(obj_name), *nold, *nold);
            return M_OPT_OUT_OF_RANGE;
        }
        r = m_config_set_option_cli(config, bstr0(opt), val, flags);
        if (r < 0) {
            if (r != M_OPT_EXIT)
                mp_err(log, "Option %.*s: "
                       "Error while parsing %.*s parameter %s (%.*s)\n",
                       BSTR_P(opt_name), BSTR_P(obj_name), opt, BSTR_P(val));
            return r;
        }
        *out_name = bstr0(opt);
        *out_val = val;
        (*nold)++;
        return 1;
    }
}