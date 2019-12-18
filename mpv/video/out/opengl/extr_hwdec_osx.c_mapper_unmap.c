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
struct ra_hwdec_mapper {int /*<<< orphan*/ * tex; int /*<<< orphan*/  ra; struct priv* priv; } ;
struct TYPE_2__ {int num_planes; } ;
struct priv {TYPE_1__ desc; int /*<<< orphan*/ * pbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVPixelBufferRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mapper_unmap(struct ra_hwdec_mapper *mapper)
{
    struct priv *p = mapper->priv;

    // Is this sane? No idea how to release the texture without deleting it.
    CVPixelBufferRelease(p->pbuf);
    p->pbuf = NULL;

    for (int i = 0; i < p->desc.num_planes; i++)
        ra_tex_free(mapper->ra, &mapper->tex[i]);
}