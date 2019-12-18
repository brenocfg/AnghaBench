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
typedef  enum mp_component_type { ____Placeholder_mp_component_type } mp_component_type ;

/* Variables and functions */
#define  MP_COMPONENT_TYPE_FLOAT 129 
#define  MP_COMPONENT_TYPE_UINT 128 

__attribute__((used)) static const char *comp_type(enum mp_component_type type)
{
    switch (type) {
    case MP_COMPONENT_TYPE_UINT:  return "uint";
    case MP_COMPONENT_TYPE_FLOAT: return "float";
    default: return "unknown";
    }
}