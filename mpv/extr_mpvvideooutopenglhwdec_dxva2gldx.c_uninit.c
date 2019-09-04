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
struct ra_hwdec {int /*<<< orphan*/  devs; struct priv_owner* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  av_device_ref; } ;
struct priv_owner {scalar_t__ device; TYPE_1__ hwctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DDevice9Ex_Release (scalar_t__) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwdec_devices_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void uninit(struct ra_hwdec *hw)
{
    struct priv_owner *p = hw->priv;

    hwdec_devices_remove(hw->devs, &p->hwctx);
    av_buffer_unref(&p->hwctx.av_device_ref);

    if (p->device)
        IDirect3DDevice9Ex_Release(p->device);
}