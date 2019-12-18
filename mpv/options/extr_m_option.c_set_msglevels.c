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
struct mpv_node {int dummy; } ;
typedef  int /*<<< orphan*/  m_option_t ;
struct TYPE_2__ {int (* set ) (int /*<<< orphan*/  const*,char***,struct mpv_node*) ;int /*<<< orphan*/  (* free ) (char***) ;int /*<<< orphan*/  (* copy ) (int /*<<< orphan*/  const*,void*,char***) ;} ;

/* Variables and functions */
 int check_msg_levels (int /*<<< orphan*/ ,char**) ; 
 TYPE_1__ m_option_type_keyvalue_list ; 
 int /*<<< orphan*/  mp_null_log ; 
 int stub1 (int /*<<< orphan*/  const*,char***,struct mpv_node*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/  const*,void*,char***) ; 
 int /*<<< orphan*/  stub3 (char***) ; 

__attribute__((used)) static int set_msglevels(const m_option_t *opt, void *dst,
                             struct mpv_node *src)
{
    char **dst_copy = NULL;
    int r = m_option_type_keyvalue_list.set(opt, &dst_copy, src);
    if (r >= 0)
        r = check_msg_levels(mp_null_log, dst_copy);

    if (r >= 0)
        m_option_type_keyvalue_list.copy(opt, dst, &dst_copy);
    m_option_type_keyvalue_list.free(&dst_copy);
    return r;
}