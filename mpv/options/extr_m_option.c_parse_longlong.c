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
struct mp_log {int dummy; } ;
struct bstr {scalar_t__ len; } ;
struct TYPE_3__ {int flags; long long min; long long max; } ;
typedef  TYPE_1__ m_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (struct bstr) ; 
 int M_OPT_INVALID ; 
 int M_OPT_MAX ; 
 int M_OPT_MIN ; 
 int M_OPT_MISSING_PARAM ; 
 int M_OPT_OUT_OF_RANGE ; 
 long long bstrtoll (struct bstr,struct bstr*,int) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static int parse_longlong(struct mp_log *log, const m_option_t *opt,
                          struct bstr name, struct bstr param, void *dst)
{
    if (param.len == 0)
        return M_OPT_MISSING_PARAM;

    struct bstr rest;
    long long tmp_int = bstrtoll(param, &rest, 10);
    if (rest.len)
        tmp_int = bstrtoll(param, &rest, 0);
    if (rest.len) {
        mp_err(log, "The %.*s option must be an integer: %.*s\n",
               BSTR_P(name), BSTR_P(param));
        return M_OPT_INVALID;
    }

    if ((opt->flags & M_OPT_MIN) && (tmp_int < opt->min)) {
        mp_err(log, "The %.*s option must be >= %d: %.*s\n",
               BSTR_P(name), (int) opt->min, BSTR_P(param));
        return M_OPT_OUT_OF_RANGE;
    }

    if ((opt->flags & M_OPT_MAX) && (tmp_int > opt->max)) {
        mp_err(log, "The %.*s option must be <= %d: %.*s\n",
               BSTR_P(name), (int) opt->max, BSTR_P(param));
        return M_OPT_OUT_OF_RANGE;
    }

    if (dst)
        *(long long *)dst = tmp_int;

    return 1;
}