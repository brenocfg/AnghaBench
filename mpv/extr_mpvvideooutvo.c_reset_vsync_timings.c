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
struct vo_internal {int expecting_vsync; scalar_t__ num_successive_vsyncs; scalar_t__ base_vsync; scalar_t__ drop_point; } ;
struct vo {struct vo_internal* in; } ;

/* Variables and functions */

__attribute__((used)) static void reset_vsync_timings(struct vo *vo)
{
    struct vo_internal *in = vo->in;
    in->drop_point = 0;
    in->base_vsync = 0;
    in->expecting_vsync = false;
    in->num_successive_vsyncs = 0;
}