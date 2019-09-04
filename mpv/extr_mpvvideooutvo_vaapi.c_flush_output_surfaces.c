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
struct priv {scalar_t__ visible_surface; scalar_t__ output_surface; int /*<<< orphan*/ * output_surfaces; } ;

/* Variables and functions */
 int MAX_OUTPUT_SURFACES ; 
 int /*<<< orphan*/  mp_image_unrefp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flush_output_surfaces(struct priv *p)
{
    for (int n = 0; n < MAX_OUTPUT_SURFACES; n++)
        mp_image_unrefp(&p->output_surfaces[n]);
    p->output_surface = 0;
    p->visible_surface = 0;
}