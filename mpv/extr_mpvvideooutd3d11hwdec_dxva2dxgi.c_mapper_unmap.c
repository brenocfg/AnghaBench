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
struct ra_hwdec_mapper {scalar_t__* tex; struct priv* priv; } ;
struct priv {size_t queue_pos; size_t queue_len; TYPE_1__** queue; } ;
struct TYPE_2__ {scalar_t__ tex; } ;

/* Variables and functions */
 int /*<<< orphan*/  surf_release (struct ra_hwdec_mapper*) ; 

__attribute__((used)) static void mapper_unmap(struct ra_hwdec_mapper *mapper)
{
    struct priv *p = mapper->priv;

    if (p->queue_pos < p->queue_len &&
        p->queue[p->queue_pos]->tex == mapper->tex[0])
    {
        surf_release(mapper);
        mapper->tex[0] = NULL;
    }
}