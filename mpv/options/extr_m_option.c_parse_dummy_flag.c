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
 int M_OPT_DISALLOW_PARAM ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_dummy_flag(struct mp_log *log, const m_option_t *opt,
                            struct bstr name, struct bstr param, void *dst)
{
    if (param.len) {
        mp_err(log, "Invalid parameter for %.*s flag: %.*s\n",
               BSTR_P(name), BSTR_P(param));
        return M_OPT_DISALLOW_PARAM;
    }
    return 0;
}