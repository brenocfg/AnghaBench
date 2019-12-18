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
struct TYPE_3__ {unsigned long long monotonic; unsigned long long realtime; } ;
typedef  TYPE_1__ heartbeat_t ;

/* Variables and functions */

inline void heartbeat_init(heartbeat_t *hb)
{
    hb->monotonic = hb->realtime = 0ULL;
}