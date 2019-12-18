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
struct wined3d_device {struct shader_glsl_priv* shader_priv; } ;
struct constant_heap {int dummy; } ;
struct shader_glsl_priv {int /*<<< orphan*/  next_constant_version; struct constant_heap pconst_heap; } ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  update_heap_entry (struct constant_heap*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_glsl_update_float_pixel_constants(struct wined3d_device *device, UINT start, UINT count)
{
    struct shader_glsl_priv *priv = device->shader_priv;
    struct constant_heap *heap = &priv->pconst_heap;
    UINT i;

    for (i = start; i < count + start; ++i)
    {
        update_heap_entry(heap, i, priv->next_constant_version);
    }
}