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
struct bstr {int /*<<< orphan*/  start; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (struct bstr) ; 
 int M_OPT_EXIT ; 
 int M_OPT_INVALID ; 
 struct bstr bstr0 (int /*<<< orphan*/ *) ; 
 int bstr_equals0 (struct bstr,char*) ; 
 int mp_d3d11_list_or_verify_adapters (struct mp_log*,struct bstr,struct bstr*) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int d3d11_validate_adapter(struct mp_log *log,
                                  const struct m_option *opt,
                                  struct bstr name, struct bstr param)
{
    bool help = bstr_equals0(param, "help");
    bool adapter_matched = false;
    struct bstr listing = { 0 };

    if (bstr_equals0(param, "")) {
        return 0;
    }

    adapter_matched = mp_d3d11_list_or_verify_adapters(log,
                                                       help ? bstr0(NULL) : param,
                                                       help ? &listing : NULL);

    if (help) {
        mp_info(log, "Available D3D11 adapters:\n%.*s",
                BSTR_P(listing));
        talloc_free(listing.start);
        return M_OPT_EXIT;
    }

    if (!adapter_matched) {
        mp_err(log, "No adapter matching '%.*s'!\n", BSTR_P(param));
    }

    return adapter_matched ? 0 : M_OPT_INVALID;
}