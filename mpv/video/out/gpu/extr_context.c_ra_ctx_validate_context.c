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
struct m_option {int dummy; } ;
struct bstr {int dummy; } ;
struct TYPE_3__ {char* name; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int MP_ARRAY_SIZE (TYPE_1__**) ; 
 int M_OPT_EXIT ; 
 int M_OPT_INVALID ; 
 scalar_t__ bstr_equals0 (struct bstr,char*) ; 
 TYPE_1__** contexts ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,...) ; 

int ra_ctx_validate_context(struct mp_log *log, const struct m_option *opt,
                            struct bstr name, struct bstr param)
{
    if (bstr_equals0(param, "help")) {
        mp_info(log, "GPU contexts (APIs):\n");
        mp_info(log, "    auto (autodetect)\n");
        for (int n = 0; n < MP_ARRAY_SIZE(contexts); n++)
            mp_info(log, "    %s (%s)\n", contexts[n]->name, contexts[n]->type);
        return M_OPT_EXIT;
    }
    if (bstr_equals0(param, "auto"))
        return 1;
    for (int i = 0; i < MP_ARRAY_SIZE(contexts); i++) {
        if (bstr_equals0(param, contexts[i]->name))
            return 1;
    }
    return M_OPT_INVALID;
}