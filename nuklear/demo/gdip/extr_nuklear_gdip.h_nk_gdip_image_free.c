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
struct TYPE_2__ {int /*<<< orphan*/  ptr; } ;
struct nk_image {TYPE_1__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ ) ; 

void
nk_gdip_image_free(struct nk_image image)
{
    if (!image.handle.ptr)
        return;
    GdipDisposeImage(image.handle.ptr);
}