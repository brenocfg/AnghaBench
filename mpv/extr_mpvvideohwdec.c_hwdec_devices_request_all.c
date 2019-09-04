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
struct mp_hwdec_devices {int /*<<< orphan*/  load_api_ctx; int /*<<< orphan*/  (* load_api ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hwdec_devices_get_first (struct mp_hwdec_devices*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void hwdec_devices_request_all(struct mp_hwdec_devices *devs)
{
    if (devs->load_api && !hwdec_devices_get_first(devs))
        devs->load_api(devs->load_api_ctx);
}