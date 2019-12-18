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
struct wined3d_cs {int /*<<< orphan*/  fb; int /*<<< orphan*/  state; TYPE_1__* device; } ;
struct wined3d_adapter {int /*<<< orphan*/  d3d_info; int /*<<< orphan*/  gl_info; } ;
struct TYPE_2__ {struct wined3d_adapter* adapter; } ;

/* Variables and functions */
 int WINED3D_STATE_INIT_DEFAULT ; 
 int WINED3D_STATE_NO_REF ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  state_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void wined3d_cs_exec_reset_state(struct wined3d_cs *cs, const void *data)
{
    struct wined3d_adapter *adapter = cs->device->adapter;

    state_cleanup(&cs->state);
    memset(&cs->state, 0, sizeof(cs->state));
    state_init(&cs->state, &cs->fb, &adapter->gl_info, &adapter->d3d_info,
            WINED3D_STATE_NO_REF | WINED3D_STATE_INIT_DEFAULT);
}