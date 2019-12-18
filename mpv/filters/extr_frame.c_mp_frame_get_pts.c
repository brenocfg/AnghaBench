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
struct mp_frame {size_t type; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {double (* get_pts ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 TYPE_1__* frame_handlers ; 
 double stub1 (int /*<<< orphan*/ ) ; 

double mp_frame_get_pts(struct mp_frame frame)
{
    if (frame_handlers[frame.type].get_pts)
        return frame_handlers[frame.type].get_pts(frame.data);
    return MP_NOPTS_VALUE;
}