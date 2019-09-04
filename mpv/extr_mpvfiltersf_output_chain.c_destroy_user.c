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
struct mp_user_filter {int /*<<< orphan*/  args; } ;
struct mp_filter {struct mp_user_filter* priv; } ;
struct m_option {int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_option_free (struct m_option*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_option_type_obj_settings_list ; 
 int /*<<< orphan*/  mp_filter_free_children (struct mp_filter*) ; 

__attribute__((used)) static void destroy_user(struct mp_filter *f)
{
    struct mp_user_filter *u = f->priv;

    struct m_option dummy = {.type = &m_option_type_obj_settings_list};
    m_option_free(&dummy, &u->args);

    mp_filter_free_children(f);
}