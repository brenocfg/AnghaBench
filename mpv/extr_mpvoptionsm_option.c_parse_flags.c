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
struct m_option {struct m_opt_choice_alternatives* priv; } ;
struct m_opt_choice_alternatives {scalar_t__ name; } ;
struct bstr {scalar_t__ len; } ;
typedef  struct bstr bstr ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (struct bstr) ; 
 int M_OPT_INVALID ; 
 int M_OPT_UNKNOWN ; 
 int apply_flag (struct m_option const*,int*,struct bstr) ; 
 int /*<<< orphan*/  bstr_split_tok (struct bstr,char*,struct bstr*,struct bstr*) ; 
 int /*<<< orphan*/  mp_fatal (struct mp_log*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,...) ; 

__attribute__((used)) static int parse_flags(struct mp_log *log, const struct m_option *opt,
                       struct bstr name, struct bstr param, void *dst)
{
    int value = 0;
    while (param.len) {
        bstr flag;
        bstr_split_tok(param, "+", &flag, &param);
        int r = apply_flag(opt, &value, flag);
        if (r == M_OPT_UNKNOWN) {
            mp_fatal(log, "Invalid flag for option %.*s: %.*s\n",
                     BSTR_P(name), BSTR_P(flag));
            mp_info(log, "Valid flags are:\n");
            struct m_opt_choice_alternatives *alt;
            for (alt = opt->priv; alt->name; alt++)
                mp_info(log, "    %s\n", alt->name);
            mp_info(log, "Flags can usually be combined with '+'.\n");
            return M_OPT_INVALID;
        } else if (r < 0) {
            mp_fatal(log, "Option %.*s: flag '%.*s' conflicts with a previous "
                     "flag value.\n", BSTR_P(name), BSTR_P(flag));
            return M_OPT_INVALID;
        }
    }
    if (dst)
        *(int *)dst = value;
    return 1;
}