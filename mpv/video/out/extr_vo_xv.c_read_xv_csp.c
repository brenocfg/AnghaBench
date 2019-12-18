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
struct xvctx {scalar_t__ cached_csp; int /*<<< orphan*/  xv_port; } ;
struct vo {struct xvctx* priv; } ;

/* Variables and functions */
 scalar_t__ MP_CSP_BT_601 ; 
 scalar_t__ MP_CSP_BT_709 ; 
 scalar_t__ xv_get_eq (struct vo*,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static void read_xv_csp(struct vo *vo)
{
    struct xvctx *ctx = vo->priv;
    ctx->cached_csp = 0;
    int bt709_enabled;
    if (xv_get_eq(vo, ctx->xv_port, "bt_709", &bt709_enabled))
        ctx->cached_csp = bt709_enabled == 100 ? MP_CSP_BT_709 : MP_CSP_BT_601;
}