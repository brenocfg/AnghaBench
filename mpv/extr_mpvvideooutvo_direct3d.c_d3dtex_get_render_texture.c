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
struct d3dtex {scalar_t__ system; scalar_t__ device; } ;
typedef  int /*<<< orphan*/  d3d_priv ;
typedef  int /*<<< orphan*/  IDirect3DBaseTexture9 ;

/* Variables and functions */

__attribute__((used)) static IDirect3DBaseTexture9 *d3dtex_get_render_texture(d3d_priv *priv,
                                                        struct d3dtex *tex)
{
    return (IDirect3DBaseTexture9 *)(tex->device ? tex->device : tex->system);
}