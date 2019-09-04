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
typedef  int /*<<< orphan*/  D3DCOLOR ;

/* Variables and functions */
 int /*<<< orphan*/  RGBA_MAKE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3drm_color_component (float) ; 

__attribute__((used)) static inline void d3drm_set_color(D3DCOLOR *color, float r, float g, float b, float a)
{
    *color = RGBA_MAKE(d3drm_color_component(r), d3drm_color_component(g),
            d3drm_color_component(b), d3drm_color_component(a));
}