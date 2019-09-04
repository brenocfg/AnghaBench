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
struct TYPE_2__ {int /*<<< orphan*/  confirm_wait; int /*<<< orphan*/  status; } ;
struct ks_wlan_private {TYPE_1__ psstatus; } ;

/* Variables and functions */
 scalar_t__ PS_ACTIVE_SET ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ps_confirm_wait_inc(struct ks_wlan_private *priv)
{
	if (atomic_read(&priv->psstatus.status) > PS_ACTIVE_SET)
		atomic_inc(&priv->psstatus.confirm_wait);
}