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
struct m_config_option {int /*<<< orphan*/  opt; } ;
struct m_config {int dummy; } ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 int M_OPT_TYPE_OPTIONAL_PARAM ; 
 int M_OPT_UNKNOWN ; 
 struct m_config_option* m_config_mogrify_cli_opt (struct m_config*,int /*<<< orphan*/ *,int*,int*) ; 
 int m_option_required_params (int /*<<< orphan*/ ) ; 

int m_config_option_requires_param(struct m_config *config, bstr name)
{
    bool negate;
    int flags;
    struct m_config_option *co =
        m_config_mogrify_cli_opt(config, &name, &negate, &flags);

    if (!co)
        return M_OPT_UNKNOWN;

    if (negate || (flags & M_OPT_TYPE_OPTIONAL_PARAM))
        return 0;

    return m_option_required_params(co->opt);
}