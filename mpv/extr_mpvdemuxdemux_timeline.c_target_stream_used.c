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
struct segment {int num_stream_map; int* stream_map; } ;

/* Variables and functions */

__attribute__((used)) static bool target_stream_used(struct segment *seg, int target_index)
{
    for (int n = 0; n < seg->num_stream_map; n++) {
        if (seg->stream_map[n] == target_index)
            return true;
    }
    return false;
}