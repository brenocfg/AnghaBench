#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct m_config_option {TYPE_1__* opt; } ;
struct m_config {int dummy; } ;
struct bstr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 struct m_config_option* m_config_get_co_any (struct m_config const*,struct bstr) ; 
 int /*<<< orphan*/  m_option_type_cli_alias ; 

struct m_config_option *m_config_get_co(const struct m_config *config,
                                        struct bstr name)
{
    struct m_config_option *co = m_config_get_co_any(config, name);
    // CLI aliases should not be real options, and are explicitly handled by
    // m_config_set_option_cli(). So pretend it does not exist.
    if (co && co->opt->type == &m_option_type_cli_alias)
        co = NULL;
    return co;
}