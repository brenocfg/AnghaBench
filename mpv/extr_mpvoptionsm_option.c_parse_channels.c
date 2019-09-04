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
struct mp_chmap {int /*<<< orphan*/  member_0; } ;
struct m_channels {int set; int auto_safe; int /*<<< orphan*/  chmaps; int /*<<< orphan*/  num_chmaps; int /*<<< orphan*/  member_0; } ;
struct bstr {scalar_t__ len; } ;
struct TYPE_3__ {int min; } ;
typedef  TYPE_1__ m_option_t ;
typedef  struct bstr bstr ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (struct bstr) ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mp_chmap) ; 
 int M_OPT_EXIT ; 
 int M_OPT_INVALID ; 
 int bstr_equals0 (struct bstr,char*) ; 
 int /*<<< orphan*/  bstr_split_tok (struct bstr,char*,struct bstr*,struct bstr*) ; 
 int /*<<< orphan*/  mp_chmap_from_str (struct mp_chmap*,struct bstr) ; 
 int /*<<< orphan*/  mp_chmap_is_valid (struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_print_help (struct mp_log*) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,...) ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_channels(struct mp_log *log, const m_option_t *opt,
                          struct bstr name, struct bstr param, void *dst)
{
    // see OPT_CHANNELS for semantics.
    bool limited = opt->min;

    struct m_channels res = {0};

    if (bstr_equals0(param, "help")) {
        mp_chmap_print_help(log);
        if (!limited) {
            mp_info(log, "\nOther values:\n"
                         "    auto-safe\n");
        }
        return M_OPT_EXIT;
    }

    bool auto_safe = bstr_equals0(param, "auto-safe");
    if (bstr_equals0(param, "auto") || bstr_equals0(param, "empty") || auto_safe) {
        if (limited) {
            mp_err(log, "Disallowed parameter.\n");
            return M_OPT_INVALID;
        }
        param.len = 0;
        res.set = true;
        res.auto_safe = auto_safe;
    }

    while (param.len) {
        bstr item;
        if (limited) {
            item = param;
            param.len = 0;
        } else {
            bstr_split_tok(param, ",", &item, &param);
        }

        struct mp_chmap map = {0};
        if (!mp_chmap_from_str(&map, item) || !mp_chmap_is_valid(&map)) {
            mp_err(log, "Invalid channel layout: %.*s\n", BSTR_P(item));
            talloc_free(res.chmaps);
            return M_OPT_INVALID;
        }

        MP_TARRAY_APPEND(NULL, res.chmaps, res.num_chmaps, map);
        res.set = true;
    }

    if (dst) {
        *(struct m_channels *)dst = res;
    } else {
        talloc_free(res.chmaps);
    }

    return 1;
}