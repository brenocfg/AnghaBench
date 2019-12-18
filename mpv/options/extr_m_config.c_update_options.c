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
struct m_group_data {scalar_t__ ts; scalar_t__ udata; } ;
struct m_config_group {TYPE_2__* group; } ;
struct m_config_data {TYPE_1__* shadow; scalar_t__ num_gdata; scalar_t__ group_index; int /*<<< orphan*/  ts; } ;
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_5__ {struct m_option* opts; } ;
struct TYPE_4__ {int num_groups; struct m_config_group* groups; } ;

/* Variables and functions */
 int MPMAX (scalar_t__,scalar_t__) ; 
 int MPMIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct m_group_data* m_config_gdata (struct m_config_data*,int) ; 
 int /*<<< orphan*/  m_option_copy (struct m_option const*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool update_options(struct m_config_data *dst, struct m_config_data *src)
{
    assert(dst->shadow == src->shadow);

    bool res = false;
    dst->ts = src->ts;

    // Must be from same root, but they can have arbitrary overlap.
    int group_s = MPMAX(dst->group_index, src->group_index);
    int group_e = MPMIN(dst->group_index + dst->num_gdata,
                        src->group_index + src->num_gdata);
    assert(group_s >= 0 && group_e <= dst->shadow->num_groups);
    for (int n = group_s; n < group_e; n++) {
        struct m_config_group *g = &dst->shadow->groups[n];
        const struct m_option *opts = g->group->opts;
        struct m_group_data *gsrc = m_config_gdata(src, n);
        struct m_group_data *gdst = m_config_gdata(dst, n);
        assert(gsrc && gdst);

        if (gdst->ts >= gsrc->ts)
            continue;
        gdst->ts = gsrc->ts;
        res = true;

        for (int i = 0; opts && opts[i].name; i++) {
            const struct m_option *opt = &opts[i];

            if (opt->offset >= 0 && opt->type->size) {
                m_option_copy(opt, gdst->udata + opt->offset,
                                   gsrc->udata + opt->offset);
            }
        }
    }

    return res;
}