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
struct TYPE_2__ {int initialized; } ;
struct packet_id {TYPE_1__ rec; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
packet_id_initialized(const struct packet_id *pid)
{
    return pid->rec.initialized;
}