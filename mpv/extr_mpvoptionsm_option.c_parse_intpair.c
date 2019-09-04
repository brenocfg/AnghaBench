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
struct m_option {int dummy; } ;
struct bstr {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (struct bstr) ; 
 int M_OPT_INVALID ; 
 int M_OPT_MISSING_PARAM ; 
 struct bstr bstr_cut (struct bstr,int) ; 
 int /*<<< orphan*/  bstr_startswith0 (struct bstr,char*) ; 
 int bstrtoll (struct bstr,struct bstr*,int) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_intpair(struct mp_log *log, const struct m_option *opt,
                         struct bstr name, struct bstr param, void *dst)
{
    if (param.len == 0)
        return M_OPT_MISSING_PARAM;

    struct bstr s = param;
    int end = -1;
    int start = bstrtoll(s, &s, 10);
    if (s.len == param.len)
        goto bad;
    if (s.len > 0) {
        if (!bstr_startswith0(s, "-"))
            goto bad;
        s = bstr_cut(s, 1);
    }
    if (s.len > 0)
        end = bstrtoll(s, &s, 10);
    if (s.len > 0)
        goto bad;

    if (dst) {
        int *p = dst;
        p[0] = start;
        p[1] = end;
    }

    return 1;

bad:
    mp_err(log, "Invalid integer range "
           "specification for option %.*s: %.*s\n",
           BSTR_P(name), BSTR_P(param));
    return M_OPT_INVALID;
}