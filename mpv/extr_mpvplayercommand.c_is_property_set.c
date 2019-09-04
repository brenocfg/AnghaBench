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
struct m_property_action_arg {int action; void* arg; } ;

/* Variables and functions */
#define  M_PROPERTY_KEY_ACTION 133 
#define  M_PROPERTY_MULTIPLY 132 
#define  M_PROPERTY_SET 131 
#define  M_PROPERTY_SET_NODE 130 
#define  M_PROPERTY_SET_STRING 129 
#define  M_PROPERTY_SWITCH 128 

__attribute__((used)) static bool is_property_set(int action, void *val)
{
    switch (action) {
    case M_PROPERTY_SET:
    case M_PROPERTY_SWITCH:
    case M_PROPERTY_SET_STRING:
    case M_PROPERTY_SET_NODE:
    case M_PROPERTY_MULTIPLY:
        return true;
    case M_PROPERTY_KEY_ACTION: {
        struct m_property_action_arg *key = val;
        return is_property_set(key->action, key->arg);
    }
    default:
        return false;
    }
}