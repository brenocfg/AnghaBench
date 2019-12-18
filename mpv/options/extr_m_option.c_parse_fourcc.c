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
typedef  int uint8_t ;
struct mp_log {int dummy; } ;
struct bstr {int len; int* start; } ;
typedef  int /*<<< orphan*/  m_option_t ;
struct TYPE_3__ {scalar_t__ len; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (struct bstr) ; 
 int M_OPT_INVALID ; 
 int M_OPT_MISSING_PARAM ; 
 unsigned int bstrtoll (struct bstr,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_fourcc(struct mp_log *log, const m_option_t *opt,
                        struct bstr name, struct bstr param, void *dst)
{
    if (param.len == 0)
        return M_OPT_MISSING_PARAM;

    unsigned int value;

    if (param.len == 4) {
        uint8_t *s = param.start;
        value = s[0] | (s[1] << 8) | (s[2] << 16) | (s[3] << 24);
    } else {
        bstr rest;
        value = bstrtoll(param, &rest, 16);
        if (rest.len != 0) {
            mp_err(log, "Option %.*s: invalid FourCC: '%.*s'\n",
                   BSTR_P(name), BSTR_P(param));
            return M_OPT_INVALID;
        }
    }

    if (dst)
        *((unsigned int *)dst) = value;

    return 1;
}