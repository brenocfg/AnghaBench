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
struct TYPE_3__ {scalar_t__ palette_size; scalar_t__ palette; scalar_t__ rgb; int /*<<< orphan*/  buffer1; int /*<<< orphan*/  blue_mask; int /*<<< orphan*/  green_mask; int /*<<< orphan*/  red_mask; } ;
typedef  TYPE_1__ D3DRMIMAGE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL d3drm_validate_image(D3DRMIMAGE *image)
{
    if (!image
            || !image->red_mask
            || !image->green_mask
            || !image->blue_mask
            || !image->buffer1
            || !(image->rgb || (image->palette && image->palette_size)))
    {
        return FALSE;
    }

    return TRUE;
}