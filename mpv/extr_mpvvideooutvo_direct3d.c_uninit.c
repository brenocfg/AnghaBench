#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vo {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/ * d3d9_dll; } ;
typedef  TYPE_1__ d3d_priv ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  uninit_d3d (TYPE_1__*) ; 
 int /*<<< orphan*/  vo_w32_uninit (struct vo*) ; 

__attribute__((used)) static void uninit(struct vo *vo)
{
    d3d_priv *priv = vo->priv;

    MP_VERBOSE(priv, "uninit called.\n");

    uninit_d3d(priv);
    vo_w32_uninit(vo);
    if (priv->d3d9_dll)
        FreeLibrary(priv->d3d9_dll);
    priv->d3d9_dll = NULL;
}