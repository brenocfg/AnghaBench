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
struct TYPE_2__ {int /*<<< orphan*/  start; int /*<<< orphan*/  len; } ;
struct pass_info {TYPE_1__ desc; int /*<<< orphan*/  perf; } ;
struct mp_frame_perf {size_t count; int /*<<< orphan*/ * desc; int /*<<< orphan*/ * perf; } ;

/* Variables and functions */
 int VO_PASS_PERF_MAX ; 

__attribute__((used)) static void frame_perf_data(struct pass_info pass[], struct mp_frame_perf *out)
{
    for (int i = 0; i < VO_PASS_PERF_MAX; i++) {
        if (!pass[i].desc.len)
            break;
        out->perf[out->count] = pass[i].perf;
        out->desc[out->count] = pass[i].desc.start;
        out->count++;
    }
}