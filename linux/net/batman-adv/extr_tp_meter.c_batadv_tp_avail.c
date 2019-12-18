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
typedef  size_t u32 ;
struct batadv_tp_vars {size_t cwnd; size_t last_sent; int /*<<< orphan*/  last_acked; } ;

/* Variables and functions */
 size_t atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool batadv_tp_avail(struct batadv_tp_vars *tp_vars,
			    size_t payload_len)
{
	u32 win_left, win_limit;

	win_limit = atomic_read(&tp_vars->last_acked) + tp_vars->cwnd;
	win_left = win_limit - tp_vars->last_sent;

	return win_left >= payload_len;
}