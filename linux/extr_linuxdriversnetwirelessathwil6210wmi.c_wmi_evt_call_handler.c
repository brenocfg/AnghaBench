#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
struct wil6210_vif {int dummy; } ;
struct TYPE_3__ {int eventid; int /*<<< orphan*/  (* handler ) (struct wil6210_vif*,int,void*,int) ;} ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct wil6210_vif*,int,void*,int) ; 
 TYPE_1__* wmi_evt_handlers ; 

__attribute__((used)) static bool wmi_evt_call_handler(struct wil6210_vif *vif, int id,
				 void *d, int len)
{
	uint i;

	for (i = 0; i < ARRAY_SIZE(wmi_evt_handlers); i++) {
		if (wmi_evt_handlers[i].eventid == id) {
			wmi_evt_handlers[i].handler(vif, id, d, len);
			return true;
		}
	}

	return false;
}