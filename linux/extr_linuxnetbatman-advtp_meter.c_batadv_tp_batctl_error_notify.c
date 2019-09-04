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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct batadv_priv {int dummy; } ;
typedef  enum batadv_tp_meter_reason { ____Placeholder_batadv_tp_meter_reason } batadv_tp_meter_reason ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_tp_batctl_notify (int,int /*<<< orphan*/  const*,struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_tp_batctl_error_notify(enum batadv_tp_meter_reason reason,
					  const u8 *dst,
					  struct batadv_priv *bat_priv,
					  u32 cookie)
{
	batadv_tp_batctl_notify(reason, dst, bat_priv, 0, 0, cookie);
}