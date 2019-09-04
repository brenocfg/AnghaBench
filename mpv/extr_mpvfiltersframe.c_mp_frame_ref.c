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
struct TYPE_2__ {int /*<<< orphan*/  (* new_ref ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t MP_FRAME_NONE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* frame_handlers ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

struct mp_frame mp_frame_ref(struct mp_frame frame)
{
    if (frame_handlers[frame.type].new_ref) {
        assert(frame.data);
        frame.data = frame_handlers[frame.type].new_ref(frame.data);
        if (!frame.data)
            frame.type = MP_FRAME_NONE;
    }
    return frame;
}