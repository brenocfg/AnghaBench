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
struct ra_hwdec_mapper {struct priv* priv; } ;
struct priv {int mapped; int /*<<< orphan*/  vdp_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDP_INVALID_HANDLE ; 

__attribute__((used)) static void mark_vdpau_objects_uninitialized(struct ra_hwdec_mapper *mapper)
{
    struct priv *p = mapper->priv;

    p->vdp_surface = VDP_INVALID_HANDLE;
    p->mapped = false;
}