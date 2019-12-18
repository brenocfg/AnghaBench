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
struct vaapi_osd_image {scalar_t__ subpic_id; TYPE_1__ image; } ;
struct priv {int /*<<< orphan*/  display; } ;

/* Variables and functions */
 scalar_t__ VA_INVALID_ID ; 
 int /*<<< orphan*/  vaDestroyImage (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vaDestroySubpicture (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void free_subpicture(struct priv *p, struct vaapi_osd_image *img)
{
    if (img->image.image_id != VA_INVALID_ID)
        vaDestroyImage(p->display, img->image.image_id);
    if (img->subpic_id != VA_INVALID_ID)
        vaDestroySubpicture(p->display, img->subpic_id);
    img->image.image_id = VA_INVALID_ID;
    img->subpic_id = VA_INVALID_ID;
}