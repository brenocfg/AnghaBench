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
struct m_profile {int /*<<< orphan*/  name; struct m_profile* next; } ;
struct m_config {struct m_profile* profiles; } ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 scalar_t__ bstr_equals0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct m_profile *m_config_get_profile(const struct m_config *config, bstr name)
{
    for (struct m_profile *p = config->profiles; p; p = p->next) {
        if (bstr_equals0(name, p->name))
            return p;
    }
    return NULL;
}