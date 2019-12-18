#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mpv_node {int dummy; } ;
struct TYPE_6__ {TYPE_1__* type; } ;
typedef  TYPE_2__ m_option_t ;
struct TYPE_5__ {int (* get ) (TYPE_2__ const*,void*,struct mpv_node*,void*) ;} ;

/* Variables and functions */
 int M_OPT_UNKNOWN ; 
 int stub1 (TYPE_2__ const*,void*,struct mpv_node*,void*) ; 

__attribute__((used)) static inline int m_option_get_node(const m_option_t *opt, void *ta_parent,
                                    struct mpv_node *dst, void *src)
{
    if (opt->type->get)
        return opt->type->get(opt, ta_parent, dst, src);
    return M_OPT_UNKNOWN;
}