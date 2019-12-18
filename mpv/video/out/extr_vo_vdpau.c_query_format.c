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
struct vo {struct vdpctx* priv; } ;
struct vdpctx {int /*<<< orphan*/  force_yuv; } ;

/* Variables and functions */
 scalar_t__ mp_vdpau_get_format (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_vdpau_get_rgb_format (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_format(struct vo *vo, int format)
{
    struct vdpctx *vc = vo->priv;

    if (mp_vdpau_get_format(format, NULL, NULL))
        return 1;
    if (!vc->force_yuv && mp_vdpau_get_rgb_format(format, NULL))
        return 1;
    return 0;
}