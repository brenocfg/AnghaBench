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
typedef  int /*<<< orphan*/  packet_id_type ;
typedef  int /*<<< orphan*/  net_time_t ;

/* Variables and functions */

__attribute__((used)) static inline int
packet_id_size(bool long_form)
{
    return sizeof(packet_id_type) + (long_form ? sizeof(net_time_t) : 0);
}