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
struct m_property {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_SUB ; 
 int property_switch_track (struct m_property*,int,void*,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mp_property_sub2(void *ctx, struct m_property *prop,
                            int action, void *arg)
{
    return property_switch_track(prop, action, arg, ctx, 1, STREAM_SUB);
}