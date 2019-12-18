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
struct observe_property {int /*<<< orphan*/  async_value; scalar_t__ type; int /*<<< orphan*/  value; int /*<<< orphan*/  async_updating; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  m_option_free (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void property_free(void *p)
{
    struct observe_property *prop = p;

    assert(!prop->async_updating);

    if (prop->type) {
        m_option_free(prop->type, &prop->value);
        m_option_free(prop->type, &prop->async_value);
    }
}