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
struct wkup_m3_ipc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_1__* m3_ipc_state ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 

void wkup_m3_ipc_put(struct wkup_m3_ipc *m3_ipc)
{
	if (m3_ipc_state)
		put_device(m3_ipc_state->dev);
}