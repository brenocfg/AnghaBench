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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_STATE_INIT ; 
 int /*<<< orphan*/  DRV_RTCC_Start () ; 
 TYPE_1__ appData ; 
 int /*<<< orphan*/  mg_mgr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgr ; 

void APP_Initialize(void) {
  appData.state = APP_STATE_INIT;
  DRV_RTCC_Start();
  mg_mgr_init(&mgr, NULL);
}