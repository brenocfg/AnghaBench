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
 int get_current_pos_ratio (int /*<<< orphan*/ *,int) ; 
 int get_frame_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lrint (int) ; 
 int m_property_int_ro (int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mp_property_frame_number(void *ctx, struct m_property *prop,
                                    int action, void *arg)
{
    MPContext *mpctx = ctx;
    int frames = get_frame_count(mpctx);
    if (frames < 0)
        return M_PROPERTY_UNAVAILABLE;

    return m_property_int_ro(action, arg,
        lrint(get_current_pos_ratio(mpctx, false) * frames));
}