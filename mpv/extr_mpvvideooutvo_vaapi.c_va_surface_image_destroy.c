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
struct TYPE_2__ {scalar_t__ image_id; } ;
struct va_surface {int is_derived; TYPE_1__ image; int /*<<< orphan*/  display; } ;

/* Variables and functions */
 scalar_t__ VA_INVALID_ID ; 
 int /*<<< orphan*/  vaDestroyImage (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void va_surface_image_destroy(struct va_surface *surface)
{
    if (!surface || surface->image.image_id == VA_INVALID_ID)
        return;
    vaDestroyImage(surface->display, surface->image.image_id);
    surface->image.image_id = VA_INVALID_ID;
    surface->is_derived = false;
}