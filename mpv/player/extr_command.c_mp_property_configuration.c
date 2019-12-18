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
 int /*<<< orphan*/  CONFIGURATION ; 
 int m_property_strdup_ro (int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mp_property_configuration(void *ctx, struct m_property *prop,
                                     int action, void *arg)
{
    return m_property_strdup_ro(action, arg, CONFIGURATION);
}