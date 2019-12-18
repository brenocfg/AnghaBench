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
struct TYPE_2__ {int enable_blend; int blend_src_rgb; int blend_dst_rgb; int blend_src_alpha; int blend_dst_alpha; } ;
struct gl_shader_cache {TYPE_1__ params; } ;
typedef  enum ra_blend { ____Placeholder_ra_blend } ra_blend ;

/* Variables and functions */

void gl_sc_blend(struct gl_shader_cache *sc,
                 enum ra_blend blend_src_rgb,
                 enum ra_blend blend_dst_rgb,
                 enum ra_blend blend_src_alpha,
                 enum ra_blend blend_dst_alpha)
{
    sc->params.enable_blend = true;
    sc->params.blend_src_rgb = blend_src_rgb;
    sc->params.blend_dst_rgb = blend_dst_rgb;
    sc->params.blend_src_alpha = blend_src_alpha;
    sc->params.blend_dst_alpha = blend_dst_alpha;
}