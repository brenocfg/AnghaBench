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
struct ra_d3d11 {int /*<<< orphan*/  ctx; } ;
struct ra {struct ra_d3d11* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID3D11DeviceContext_Flush (int /*<<< orphan*/ ) ; 

void ra_d3d11_flush(struct ra *ra)
{
    struct ra_d3d11 *p = ra->priv;
    ID3D11DeviceContext_Flush(p->ctx);
}