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
struct xvctx {int /*<<< orphan*/  xv_port; } ;
struct vo {TYPE_1__* x11; struct xvctx* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  display; } ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 scalar_t__ None ; 
 scalar_t__ Success ; 
 scalar_t__ XvSetPortAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ xv_intern_atom_if_exists (struct vo*,char*) ; 

__attribute__((used)) static int xv_enable_vsync(struct vo *vo)
{
    struct xvctx *ctx = vo->priv;
    Atom xv_atom = xv_intern_atom_if_exists(vo, "XV_SYNC_TO_VBLANK");
    if (xv_atom == None)
        return -1;
    return XvSetPortAttribute(vo->x11->display, ctx->xv_port, xv_atom, 1)
           == Success;
}