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
struct m_obj_desc {struct mp_user_filter_entry const* p; } ;
struct mp_user_filter_entry {struct m_obj_desc desc; } ;

/* Variables and functions */

__attribute__((used)) static bool get_desc_from(const struct mp_user_filter_entry **list, int num,
                          struct m_obj_desc *dst, int index)
{
    if (index >= num)
        return false;
    const struct mp_user_filter_entry *entry = list[index];
    *dst = entry->desc;
    dst->p = entry;
    return true;
}