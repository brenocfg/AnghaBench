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
typedef  int /*<<< orphan*/  obs_hotkey_id ;

/* Variables and functions */
 int /*<<< orphan*/  obs_hotkey_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void defer_hotkey_unregister(void *p_cb)
{
	obs_hotkey_unregister((obs_hotkey_id)(uintptr_t)p_cb);
}