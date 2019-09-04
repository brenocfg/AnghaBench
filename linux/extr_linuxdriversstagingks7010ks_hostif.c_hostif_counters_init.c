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
struct ks_wlan_private {int /*<<< orphan*/  rec_count; int /*<<< orphan*/  event_count; scalar_t__ dev_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hostif_counters_init(struct ks_wlan_private *priv)
{
	priv->dev_count = 0;
	atomic_set(&priv->event_count, 0);
	atomic_set(&priv->rec_count, 0);
}