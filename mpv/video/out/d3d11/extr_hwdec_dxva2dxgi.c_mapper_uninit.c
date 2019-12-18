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
struct priv {int queue_len; int /*<<< orphan*/  dev11; int /*<<< orphan*/  dev9; int /*<<< orphan*/  ctx11; int /*<<< orphan*/ * queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  surf_destroy (struct ra_hwdec_mapper*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mapper_uninit(struct ra_hwdec_mapper *mapper)
{
    struct priv *p = mapper->priv;

    for (int i = 0; i < p->queue_len; i++)
        surf_destroy(mapper, p->queue[i]);

    SAFE_RELEASE(p->ctx11);
    SAFE_RELEASE(p->dev9);
    SAFE_RELEASE(p->dev11);
}