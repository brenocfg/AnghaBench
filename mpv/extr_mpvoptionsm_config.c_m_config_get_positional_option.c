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
struct m_config_option {char const* name; int /*<<< orphan*/  is_hidden; } ;
struct m_config {int num_opts; struct m_config_option* opts; } ;

/* Variables and functions */

const char *m_config_get_positional_option(const struct m_config *config, int p)
{
    int pos = 0;
    for (int n = 0; n < config->num_opts; n++) {
        struct m_config_option *co = &config->opts[n];
        if (!co->is_hidden) {
            if (pos == p)
                return co->name;
            pos++;
        }
    }
    return NULL;
}