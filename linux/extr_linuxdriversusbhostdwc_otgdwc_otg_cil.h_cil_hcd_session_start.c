#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* hcd_cb; } ;
typedef  TYPE_2__ dwc_otg_core_if_t ;
struct TYPE_4__ {int /*<<< orphan*/  p; int /*<<< orphan*/  (* session_start ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cil_hcd_session_start(dwc_otg_core_if_t * core_if)
{
	if (core_if->hcd_cb && core_if->hcd_cb->session_start) {
		core_if->hcd_cb->session_start(core_if->hcd_cb->p);
	}
}