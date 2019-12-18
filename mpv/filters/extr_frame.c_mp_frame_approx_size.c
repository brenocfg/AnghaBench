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
struct TYPE_2__ {int (* approx_size ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* frame_handlers ; 
 int stub1 (int /*<<< orphan*/ ) ; 

int mp_frame_approx_size(struct mp_frame frame)
{
    if (frame_handlers[frame.type].approx_size)
        return frame_handlers[frame.type].approx_size(frame.data);
    return 0;
}