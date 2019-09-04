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
struct ra_hwdec_driver {char* name; } ;
struct mp_log {int dummy; } ;
struct bstr {int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (struct bstr) ; 
 int M_OPT_EXIT ; 
 int M_OPT_INVALID ; 
 int bstr_equals0 (struct bstr,char*) ; 
 int /*<<< orphan*/  mp_fatal (struct mp_log*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,...) ; 
 struct ra_hwdec_driver** ra_hwdec_drivers ; 

int ra_hwdec_validate_opt(struct mp_log *log, const m_option_t *opt,
                          struct bstr name, struct bstr param)
{
    bool help = bstr_equals0(param, "help");
    if (help)
        mp_info(log, "Available hwdecs:\n");
    for (int n = 0; ra_hwdec_drivers[n]; n++) {
        const struct ra_hwdec_driver *drv = ra_hwdec_drivers[n];
        if (help) {
            mp_info(log, "    %s\n", drv->name);
        } else if (bstr_equals0(param, drv->name)) {
            return 1;
        }
    }
    if (help) {
        mp_info(log, "    auto (behavior depends on context)\n"
                     "    all (load all hwdecs)\n"
                     "    no (do not load any and block loading on demand)\n");
        return M_OPT_EXIT;
    }
    if (!param.len)
        return 1; // "" is treated specially
    if (bstr_equals0(param, "all") || bstr_equals0(param, "auto") ||
        bstr_equals0(param, "no"))
        return 1;
    mp_fatal(log, "No hwdec backend named '%.*s' found!\n", BSTR_P(param));
    return M_OPT_INVALID;
}