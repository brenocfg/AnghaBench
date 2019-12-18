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
struct mp_log {int dummy; } ;
struct m_option {int flags; struct m_opt_choice_alternatives* priv; } ;
struct m_opt_choice_alternatives {char* name; int value; } ;
struct bstr {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (struct bstr) ; 
 int M_OPT_EXIT ; 
 int M_OPT_INVALID ; 
 int M_OPT_MAX ; 
 int M_OPT_MIN ; 
 int M_OPT_MISSING_PARAM ; 
 int /*<<< orphan*/  bstrcmp0 (struct bstr,char*) ; 
 int /*<<< orphan*/  mp_fatal (struct mp_log*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,...) ; 
 int /*<<< orphan*/  mp_null_log ; 
 int parse_longlong (int /*<<< orphan*/ ,struct m_option const*,struct bstr,struct bstr,long long*) ; 
 int /*<<< orphan*/  print_choice_values (struct mp_log*,struct m_option const*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int parse_choice(struct mp_log *log, const struct m_option *opt,
                        struct bstr name, struct bstr param, void *dst)
{
    struct m_opt_choice_alternatives *alt = opt->priv;
    for ( ; alt->name; alt++) {
        if (!bstrcmp0(param, alt->name))
            break;
    }
    if (!alt->name && param.len == 0) {
        // allow flag-style options, e.g. "--mute" implies "--mute=yes"
        for (alt = opt->priv; alt->name; alt++) {
            if (!strcmp("yes", alt->name))
                break;
        }
    }
    if (!alt->name) {
        if (!bstrcmp0(param, "help")) {
            mp_info(log, "Valid values for option %.*s are:\n", BSTR_P(name));
            print_choice_values(log, opt);
            return M_OPT_EXIT;
        }
        if (param.len == 0)
            return M_OPT_MISSING_PARAM;
        if ((opt->flags & M_OPT_MIN) && (opt->flags & M_OPT_MAX)) {
            long long val;
            if (parse_longlong(mp_null_log, opt, name, param, &val) == 1) {
                if (dst)
                    *(int *)dst = val;
                return 1;
            }
        }
        mp_fatal(log, "Invalid value for option %.*s: %.*s\n",
                 BSTR_P(name), BSTR_P(param));
        mp_info(log, "Valid values are:\n");
        print_choice_values(log, opt);
        return M_OPT_INVALID;
    }
    if (dst)
        *(int *)dst = alt->value;

    return 1;
}