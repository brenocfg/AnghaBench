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
struct m_property {int dummy; } ;
struct TYPE_2__ {double end; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int M_PROPERTY_UNAVAILABLE ; 
 TYPE_1__ get_times (void*,struct m_property*,int,void*) ; 
 int m_property_double_ro (int,void*,double) ; 

__attribute__((used)) static int mp_property_sub_end(void *ctx, struct m_property *prop,
                                int action, void *arg)
{
    double end = get_times(ctx, prop, action, arg).end;
    if (end == MP_NOPTS_VALUE)
        return M_PROPERTY_UNAVAILABLE;
    return m_property_double_ro(action, arg, end);
}