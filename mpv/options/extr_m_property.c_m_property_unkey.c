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
struct m_property_action_arg {int action; void* arg; int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 int M_PROPERTY_KEY_ACTION ; 

__attribute__((used)) static void m_property_unkey(int *action, void **arg)
{
    if (*action == M_PROPERTY_KEY_ACTION) {
        struct m_property_action_arg *ka = *arg;
        if (!ka->key[0]) {
            *action = ka->action;
            *arg = ka->arg;
        }
    }
}