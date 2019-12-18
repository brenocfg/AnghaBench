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
struct TYPE_2__ {scalar_t__ mssfix; } ;
struct options {TYPE_1__ ce; } ;
struct frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_MTU_UPPER_BOUND ; 
 int /*<<< orphan*/  frame_set_mtu_dynamic (struct frame*,scalar_t__,int /*<<< orphan*/ ) ; 

void
frame_init_mssfix(struct frame *frame, const struct options *options)
{
    if (options->ce.mssfix)
    {
        frame_set_mtu_dynamic(frame, options->ce.mssfix, SET_MTU_UPPER_BOUND);
    }
}