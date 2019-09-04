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
struct priv {TYPE_1__* sws; int /*<<< orphan*/  original_image; } ;
struct mp_image_params {int dummy; } ;
struct TYPE_2__ {struct mp_image_params src; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_image_unrefp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resize (struct vo*) ; 
 int /*<<< orphan*/  vo_x11_config_vo_window (struct vo*) ; 

__attribute__((used)) static int reconfig(struct vo *vo, struct mp_image_params *fmt)
{
    struct priv *p = vo->priv;

    mp_image_unrefp(&p->original_image);

    p->sws->src = *fmt;

    vo_x11_config_vo_window(vo);

    if (!resize(vo))
        return -1;

    return 0;
}