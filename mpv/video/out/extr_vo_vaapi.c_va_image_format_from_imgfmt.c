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
struct va_image_formats {int num; TYPE_1__* entries; } ;
struct priv {struct va_image_formats* image_formats; } ;
struct TYPE_3__ {int const fourcc; } ;
typedef  TYPE_1__ VAImageFormat ;

/* Variables and functions */
 int va_fourcc_from_imgfmt (int) ; 

__attribute__((used)) static VAImageFormat *va_image_format_from_imgfmt(struct priv *ctx,
                                                  int imgfmt)
{
    struct va_image_formats *formats = ctx->image_formats;
    const int fourcc = va_fourcc_from_imgfmt(imgfmt);
    if (!formats || !formats->num || !fourcc)
        return NULL;
    for (int i = 0; i < formats->num; i++) {
        if (formats->entries[i].fourcc == fourcc)
            return &formats->entries[i];
    }
    return NULL;
}