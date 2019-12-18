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
struct batadv_tp_vars {int reason; int /*<<< orphan*/  sending; } ;
typedef  enum batadv_tp_meter_reason { ____Placeholder_batadv_tp_meter_reason } batadv_tp_meter_reason ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_tp_sender_shutdown(struct batadv_tp_vars *tp_vars,
				      enum batadv_tp_meter_reason reason)
{
	if (!atomic_dec_and_test(&tp_vars->sending))
		return;

	tp_vars->reason = reason;
}