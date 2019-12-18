#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int arguments_off; int variables_off; } ;
typedef  TYPE_1__ call_frame_t ;

/* Variables and functions */

__attribute__((used)) static inline unsigned local_off(call_frame_t *frame, int ref)
{
    return ref < 0
        ? frame->arguments_off - ref-1
        : frame->variables_off + ref;
}