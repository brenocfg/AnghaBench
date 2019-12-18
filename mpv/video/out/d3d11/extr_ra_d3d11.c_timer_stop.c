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
typedef  int /*<<< orphan*/  uint64_t ;
struct ra_d3d11 {int /*<<< orphan*/  ctx; } ;
struct ra {struct ra_d3d11* priv; } ;
struct d3d_timer {int /*<<< orphan*/  result; scalar_t__ disjoint; scalar_t__ ts_end; } ;
typedef  struct d3d_timer ra_timer ;
typedef  int /*<<< orphan*/  ID3D11Asynchronous ;

/* Variables and functions */
 int /*<<< orphan*/  ID3D11DeviceContext_End (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t timer_stop(struct ra *ra, ra_timer *ratimer)
{
    struct ra_d3d11 *p = ra->priv;
    struct d3d_timer *timer = ratimer;

    ID3D11DeviceContext_End(p->ctx, (ID3D11Asynchronous *)timer->ts_end);
    ID3D11DeviceContext_End(p->ctx, (ID3D11Asynchronous *)timer->disjoint);

    return timer->result;
}