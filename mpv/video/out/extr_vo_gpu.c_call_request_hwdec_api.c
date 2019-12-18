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

/* Variables and functions */
 int /*<<< orphan*/  VOCTRL_LOAD_HWDEC_API ; 
 int /*<<< orphan*/  vo_control (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void call_request_hwdec_api(void *ctx)
{
    // Roundabout way to run hwdec loading on the VO thread.
    // Redirects to request_hwdec_api().
    vo_control(ctx, VOCTRL_LOAD_HWDEC_API, NULL);
}