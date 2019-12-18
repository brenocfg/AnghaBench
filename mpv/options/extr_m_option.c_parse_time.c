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
struct bstr {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (struct bstr) ; 
 scalar_t__ HAS_NOPTS (int /*<<< orphan*/  const*) ; 
 double MP_NOPTS_VALUE ; 
 int M_OPT_INVALID ; 
 int M_OPT_MISSING_PARAM ; 
 scalar_t__ bstr_equals0 (struct bstr,char*) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_timestring (struct bstr,double*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_time(struct mp_log *log, const m_option_t *opt,
                      struct bstr name, struct bstr param, void *dst)
{
    if (param.len == 0)
        return M_OPT_MISSING_PARAM;

    double time = MP_NOPTS_VALUE;
    if (HAS_NOPTS(opt) && bstr_equals0(param, "no")) {
        // nothing
    } else if (!parse_timestring(param, &time, 0)) {
        mp_err(log, "Option %.*s: invalid time: '%.*s'\n",
               BSTR_P(name), BSTR_P(param));
        return M_OPT_INVALID;
    }

    if (dst)
        *(double *)dst = time;
    return 1;
}