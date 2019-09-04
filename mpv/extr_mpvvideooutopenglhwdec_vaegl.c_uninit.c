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
struct priv_owner {TYPE_1__* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  hwctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwdec_devices_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  va_destroy (TYPE_1__*) ; 

__attribute__((used)) static void uninit(struct ra_hwdec *hw)
{
    struct priv_owner *p = hw->priv;
    if (p->ctx)
        hwdec_devices_remove(hw->devs, &p->ctx->hwctx);
    va_destroy(p->ctx);
}