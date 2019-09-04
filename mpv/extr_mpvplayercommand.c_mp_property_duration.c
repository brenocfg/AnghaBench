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
typedef  int /*<<< orphan*/  MPContext ;

/* Variables and functions */
 int M_PROPERTY_UNAVAILABLE ; 
 double get_time_length (int /*<<< orphan*/ *) ; 
 int property_time (int,void*,double) ; 

__attribute__((used)) static int mp_property_duration(void *ctx, struct m_property *prop,
                                int action, void *arg)
{
    MPContext *mpctx = ctx;
    double len = get_time_length(mpctx);

    if (len < 0)
        return M_PROPERTY_UNAVAILABLE;

    return property_time(action, arg, len);
}