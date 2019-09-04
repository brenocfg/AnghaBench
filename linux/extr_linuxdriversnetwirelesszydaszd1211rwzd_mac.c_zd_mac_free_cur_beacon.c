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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct zd_mac {TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_mac_free_cur_beacon_locked (struct zd_mac*) ; 

__attribute__((used)) static void zd_mac_free_cur_beacon(struct zd_mac *mac)
{
	mutex_lock(&mac->chip.mutex);
	zd_mac_free_cur_beacon_locked(mac);
	mutex_unlock(&mac->chip.mutex);
}