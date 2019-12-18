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
struct m_profile {int num_opts; int /*<<< orphan*/ * opts; } ;
struct m_config {scalar_t__ profile_depth; } ;

/* Variables and functions */
 scalar_t__ MAX_PROFILE_DEPTH ; 
 int /*<<< orphan*/  MP_VERBOSE (struct m_config*,char*,char*) ; 
 int /*<<< orphan*/  MP_WARN (struct m_config*,char*,...) ; 
 int M_OPT_INVALID ; 
 int M_SETOPT_FROM_CONFIG_FILE ; 
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 struct m_profile* m_config_get_profile0 (struct m_config*,char*) ; 
 int /*<<< orphan*/  m_config_set_option_cli (struct m_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int m_config_set_profile(struct m_config *config, char *name, int flags)
{
    struct m_profile *p = m_config_get_profile0(config, name);
    if (!p) {
        MP_WARN(config, "Unknown profile '%s'.\n", name);
        return M_OPT_INVALID;
    }
    MP_VERBOSE(config, "Applying profile '%s'...\n", name);

    if (config->profile_depth > MAX_PROFILE_DEPTH) {
        MP_WARN(config, "WARNING: Profile inclusion too deep.\n");
        return M_OPT_INVALID;
    }
    config->profile_depth++;
    for (int i = 0; i < p->num_opts; i++) {
        m_config_set_option_cli(config,
                                bstr0(p->opts[2 * i]),
                                bstr0(p->opts[2 * i + 1]),
                                flags | M_SETOPT_FROM_CONFIG_FILE);
    }
    config->profile_depth--;

    return 0;
}