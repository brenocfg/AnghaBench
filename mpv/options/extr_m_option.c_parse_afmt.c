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
 int AF_FORMAT_COUNT ; 
 int /*<<< orphan*/  BSTR_P (struct bstr) ; 
 int M_OPT_EXIT ; 
 int M_OPT_INVALID ; 
 int M_OPT_MISSING_PARAM ; 
 int /*<<< orphan*/  af_fmt_to_str (int) ; 
 scalar_t__ bstr_equals0 (struct bstr,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstrcmp0 (struct bstr,char*) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,...) ; 

__attribute__((used)) static int parse_afmt(struct mp_log *log, const m_option_t *opt,
                      struct bstr name, struct bstr param, void *dst)
{
    if (param.len == 0)
        return M_OPT_MISSING_PARAM;

    if (!bstrcmp0(param, "help")) {
        mp_info(log, "Available formats:");
        for (int i = 1; i < AF_FORMAT_COUNT; i++)
            mp_info(log, " %s", af_fmt_to_str(i));
        mp_info(log, "\n");
        return M_OPT_EXIT;
    }

    int fmt = 0;
    for (int i = 1; i < AF_FORMAT_COUNT; i++) {
        if (bstr_equals0(param, af_fmt_to_str(i)))
            fmt = i;
    }
    if (!fmt) {
        mp_err(log, "Option %.*s: unknown format name: '%.*s'\n",
               BSTR_P(name), BSTR_P(param));
        return M_OPT_INVALID;
    }

    if (dst)
        *((int *)dst) = fmt;

    return 1;
}