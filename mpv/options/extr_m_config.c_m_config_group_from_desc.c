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
struct mpv_global {int dummy; } ;
struct mp_log {int dummy; } ;
struct m_obj_desc {int /*<<< orphan*/  priv_size; int /*<<< orphan*/  priv_defaults; int /*<<< orphan*/  options; } ;
struct m_config_group {int /*<<< orphan*/  group; } ;

/* Variables and functions */
 struct m_config_group* find_group (struct mpv_global*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mp_get_config_group (void*,struct mpv_global*,int /*<<< orphan*/ ) ; 
 void* talloc_zero_size (void*,int /*<<< orphan*/ ) ; 

void *m_config_group_from_desc(void *ta_parent, struct mp_log *log,
        struct mpv_global *global, struct m_obj_desc *desc, const char *name)
{
    const struct m_config_group *group = find_group(global, desc->options);
    if (group) {
        return mp_get_config_group(ta_parent, global, group->group);
    } else {
        void *d = talloc_zero_size(ta_parent, desc->priv_size);
        if (desc->priv_defaults)
            memcpy(d, desc->priv_defaults, desc->priv_size);
        return d;
    }
}