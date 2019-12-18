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
struct mpv_node_list {int num; TYPE_2__* values; } ;
struct TYPE_6__ {struct mpv_node_list* list; } ;
struct mpv_node {scalar_t__ format; TYPE_3__ u; } ;
typedef  int /*<<< orphan*/  m_option_t ;
struct TYPE_4__ {int /*<<< orphan*/  string; } ;
struct TYPE_5__ {scalar_t__ format; TYPE_1__ u; } ;

/* Variables and functions */
 scalar_t__ MPV_FORMAT_NODE_ARRAY ; 
 scalar_t__ MPV_FORMAT_STRING ; 
 int M_OPT_INVALID ; 
 int M_OPT_UNKNOWN ; 
 scalar_t__ apply_flag (int /*<<< orphan*/  const*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flags_set(const m_option_t *opt, void *dst, struct mpv_node *src)
{
    int value = 0;
    if (src->format != MPV_FORMAT_NODE_ARRAY)
        return M_OPT_UNKNOWN;
    struct mpv_node_list *srclist = src->u.list;
    for (int n = 0; n < srclist->num; n++) {
        if (srclist->values[n].format != MPV_FORMAT_STRING)
            return M_OPT_INVALID;
        if (apply_flag(opt, &value, bstr0(srclist->values[n].u.string)) < 0)
            return M_OPT_INVALID;
    }
    *(int *)dst = value;
    return 0;
}