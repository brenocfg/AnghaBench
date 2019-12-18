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
struct ra_d3d11 {int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_mutable; } ;
struct ra_buf {TYPE_1__ params; struct d3d_buf* priv; } ;
struct ra {struct ra_d3d11* priv; } ;
struct d3d_buf {int dirty; int /*<<< orphan*/  data; scalar_t__ buf; } ;
typedef  int /*<<< orphan*/  ID3D11Resource ;

/* Variables and functions */
 int /*<<< orphan*/  ID3D11DeviceContext_UpdateSubresource (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void buf_resolve(struct ra *ra, struct ra_buf *buf)
{
    struct ra_d3d11 *p = ra->priv;
    struct d3d_buf *buf_p = buf->priv;

    if (!buf->params.host_mutable || !buf_p->dirty)
        return;

    // Synchronize the GPU buffer with the system-memory copy
    ID3D11DeviceContext_UpdateSubresource(p->ctx, (ID3D11Resource *)buf_p->buf,
        0, NULL, buf_p->data, 0, 0);
    buf_p->dirty = false;
}