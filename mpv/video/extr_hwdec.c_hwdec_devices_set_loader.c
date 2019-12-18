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
struct mp_hwdec_devices {void (* load_api ) (void*) ;void* load_api_ctx; } ;

/* Variables and functions */

void hwdec_devices_set_loader(struct mp_hwdec_devices *devs,
    void (*load_api)(void *ctx), void *load_api_ctx)
{
    devs->load_api = load_api;
    devs->load_api_ctx = load_api_ctx;
}