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

/* Variables and functions */

__attribute__((used)) static inline char *softnet_column_name(size_t column) {
    switch(column) {
        // https://github.com/torvalds/linux/blob/a7fd20d1c476af4563e66865213474a2f9f473a4/net/core/net-procfs.c#L161-L166
        case 0: return "processed";
        case 1: return "dropped";
        case 2: return "squeezed";
        case 9: return "received_rps";
        case 10: return "flow_limit_count";
        default: return NULL;
    }
}