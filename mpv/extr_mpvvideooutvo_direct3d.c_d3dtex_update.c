#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct d3dtex {scalar_t__ device; scalar_t__ system; } ;
struct TYPE_3__ {int /*<<< orphan*/  d3d_device; } ;
typedef  TYPE_1__ d3d_priv ;
typedef  int /*<<< orphan*/  IDirect3DBaseTexture9 ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_UpdateTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool d3dtex_update(d3d_priv *priv, struct d3dtex *tex)
{
    if (!tex->device)
        return true;
    return !FAILED(IDirect3DDevice9_UpdateTexture(priv->d3d_device,
                   (IDirect3DBaseTexture9 *)tex->system,
                   (IDirect3DBaseTexture9 *)tex->device));
}