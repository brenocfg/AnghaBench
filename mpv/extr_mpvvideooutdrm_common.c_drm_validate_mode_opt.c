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
struct bstr {int dummy; } ;

/* Variables and functions */
 int M_OPT_EXIT ; 
 int M_OPT_INVALID ; 
 scalar_t__ bstr_equals0 (struct bstr,char*) ; 
 char* bstrto0 (int /*<<< orphan*/ *,struct bstr) ; 
 int /*<<< orphan*/  kms_show_available_cards_connectors_and_modes (struct mp_log*) ; 
 int /*<<< orphan*/  mp_fatal (struct mp_log*,char*) ; 
 int /*<<< orphan*/  parse_mode_spec (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static int drm_validate_mode_opt(struct mp_log *log, const struct m_option *opt,
                                 struct bstr name, struct bstr param)
{
    if (bstr_equals0(param, "help")) {
        kms_show_available_cards_connectors_and_modes(log);
        return M_OPT_EXIT;
    }

    char *spec = bstrto0(NULL, param);
    if (!parse_mode_spec(spec, NULL)) {
        mp_fatal(log, "Invalid value for option drm-mode. Must be a positive number, a string of the format WxH[@R] or 'help'\n");
        talloc_free(spec);
        return M_OPT_INVALID;
    }
    talloc_free(spec);

    return 1;
}