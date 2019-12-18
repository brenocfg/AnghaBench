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
struct vo {struct priv* priv; } ;
struct priv {TYPE_1__* sws; } ;
struct mp_image_params {int dummy; } ;
struct TYPE_2__ {struct mp_image_params src; } ;

/* Variables and functions */
 int /*<<< orphan*/  vo_wayland_reconfig (struct vo*) ; 

__attribute__((used)) static int reconfig(struct vo *vo, struct mp_image_params *params)
{
    struct priv *p = vo->priv;

    if (!vo_wayland_reconfig(vo))
        return -1;
    p->sws->src = *params;

    return 0;
}