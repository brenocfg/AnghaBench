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
struct ra_hwdec_mapper {struct priv* priv; } ;
struct priv {size_t queue_pos; size_t queue_len; TYPE_1__** queue; int /*<<< orphan*/  ctx11; } ;
struct TYPE_2__ {scalar_t__ idle11; } ;
typedef  int /*<<< orphan*/  ID3D11Asynchronous ;

/* Variables and functions */
 int /*<<< orphan*/  ID3D11DeviceContext_End (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void surf_release(struct ra_hwdec_mapper *mapper)
{
    struct priv *p = mapper->priv;
    ID3D11DeviceContext_End(p->ctx11,
        (ID3D11Asynchronous *)p->queue[p->queue_pos]->idle11);

    // The current surface is now in-flight, move to the next surface
    p->queue_pos++;
    if (p->queue_pos >= p->queue_len)
        p->queue_pos = 0;
}