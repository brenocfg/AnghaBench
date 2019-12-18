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
struct TYPE_2__ {int da; int /*<<< orphan*/  dst_name; } ;
struct j1939_sk_buff_cb {TYPE_1__ addr; } ;

/* Variables and functions */

__attribute__((used)) static inline bool j1939_cb_is_broadcast(const struct j1939_sk_buff_cb *skcb)
{
	return (!skcb->addr.dst_name && (skcb->addr.da == 0xff));
}