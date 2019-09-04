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
struct mpv_global {struct m_config_shadow* config; } ;
struct m_option {int dummy; } ;
struct m_config_shadow {struct m_config* root; } ;
struct m_config_group {TYPE_1__* group; } ;
struct m_config {int num_groups; struct m_config_group const* groups; } ;
struct TYPE_2__ {struct m_option const* opts; } ;

/* Variables and functions */

__attribute__((used)) static const struct m_config_group *find_group(struct mpv_global *global,
                                               const struct m_option *cfg)
{
    struct m_config_shadow *shadow = global->config;
    struct m_config *root = shadow->root;

    for (int n = 0; n < root->num_groups; n++) {
        if (root->groups[n].group->opts == cfg)
            return &root->groups[n];
    }

    return NULL;
}