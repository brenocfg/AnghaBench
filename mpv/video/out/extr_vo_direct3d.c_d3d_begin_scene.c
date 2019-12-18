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
struct TYPE_4__ {int d3d_in_scene; int /*<<< orphan*/  d3d_device; } ;
typedef  TYPE_1__ d3d_priv ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_BeginScene (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*) ; 

__attribute__((used)) static bool d3d_begin_scene(d3d_priv *priv)
{
    if (!priv->d3d_in_scene) {
        if (FAILED(IDirect3DDevice9_BeginScene(priv->d3d_device))) {
            MP_ERR(priv, "BeginScene failed.\n");
            return false;
        }
        priv->d3d_in_scene = true;
    }
    return true;
}