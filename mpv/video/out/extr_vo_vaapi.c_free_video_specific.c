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
struct priv {scalar_t__ pool; int /*<<< orphan*/ * swdec_surfaces; int /*<<< orphan*/  black_surface; } ;

/* Variables and functions */
 int MAX_OUTPUT_SURFACES ; 
 int /*<<< orphan*/  flush_output_surfaces (struct priv*) ; 
 int /*<<< orphan*/  mp_image_pool_clear (scalar_t__) ; 
 int /*<<< orphan*/  mp_image_unrefp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_video_specific(struct priv *p)
{
    flush_output_surfaces(p);

    mp_image_unrefp(&p->black_surface);

    for (int n = 0; n < MAX_OUTPUT_SURFACES; n++)
        mp_image_unrefp(&p->swdec_surfaces[n]);

    if (p->pool)
        mp_image_pool_clear(p->pool);
}