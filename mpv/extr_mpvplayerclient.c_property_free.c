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
struct observe_property {int /*<<< orphan*/  user_value; int /*<<< orphan*/  new_value; int /*<<< orphan*/  format; } ;
struct m_option {int dummy; } ;

/* Variables and functions */
 struct m_option* get_mp_type_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_option_free (struct m_option const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void property_free(void *p)
{
    struct observe_property *prop = p;
    const struct m_option *type = get_mp_type_get(prop->format);
    if (type) {
        m_option_free(type, &prop->new_value);
        m_option_free(type, &prop->user_value);
    }
}