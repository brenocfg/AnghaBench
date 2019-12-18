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
struct frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  frame_add_to_extra_frame (struct frame*,int) ; 

void
tls_adjust_frame_parameters(struct frame *frame)
{
    frame_add_to_extra_frame(frame, 1); /* space for opcode */
}