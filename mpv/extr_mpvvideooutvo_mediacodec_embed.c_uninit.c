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
struct vo {int /*<<< orphan*/  hwdec_devs; struct priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  av_device_ref; } ;
struct priv {TYPE_1__ hwctx; int /*<<< orphan*/  next_image; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwdec_devices_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_image_unrefp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uninit(struct vo *vo)
{
    struct priv *p = vo->priv;
    mp_image_unrefp(&p->next_image);

    hwdec_devices_remove(vo->hwdec_devs, &p->hwctx);
    av_buffer_unref(&p->hwctx.av_device_ref);
}