#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct m_option {scalar_t__ offset; TYPE_3__* type; scalar_t__ name; } ;
struct m_group_data {scalar_t__ udata; } ;
struct m_config_group {TYPE_2__* group; } ;
struct m_config_data {int num_gdata; int group_index; TYPE_1__* shadow; struct m_group_data* gdata; } ;
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_5__ {struct m_option* opts; } ;
struct TYPE_4__ {struct m_config_group* groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_option_free (struct m_option const*,scalar_t__) ; 

__attribute__((used)) static void free_option_data(void *p)
{
    struct m_config_data *data = p;

    for (int i = 0; i < data->num_gdata; i++) {
        struct m_group_data *gdata = &data->gdata[i];
        struct m_config_group *group =
            &data->shadow->groups[data->group_index + i];
        const struct m_option *opts = group->group->opts;

        for (int n = 0; opts && opts[n].name; n++) {
            const struct m_option *opt = &opts[n];

            if (opt->offset >= 0 && opt->type->size > 0)
                m_option_free(opt, gdata->udata + opt->offset);
        }
    }
}