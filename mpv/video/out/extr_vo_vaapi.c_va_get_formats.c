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
struct priv {struct va_image_formats* image_formats; int /*<<< orphan*/  display; } ;
typedef  int /*<<< orphan*/  VAStatus ;
struct TYPE_3__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_VA_STATUS (struct priv*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct priv*,char*,int) ; 
 int /*<<< orphan*/  VAImageFormat ; 
 struct va_image_formats* formats ; 
 int mp_tag_str (int /*<<< orphan*/ ) ; 
 TYPE_1__* talloc_array (struct va_image_formats*,int /*<<< orphan*/ ,int) ; 
 struct va_image_formats* talloc_ptrtype (struct priv*,int /*<<< orphan*/ ) ; 
 int vaMaxNumImageFormats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vaQueryImageFormats (int /*<<< orphan*/ ,TYPE_1__*,int*) ; 

__attribute__((used)) static void va_get_formats(struct priv *ctx)
{
    struct va_image_formats *formats = talloc_ptrtype(ctx, formats);
    formats->num = vaMaxNumImageFormats(ctx->display);
    formats->entries = talloc_array(formats, VAImageFormat, formats->num);
    VAStatus status = vaQueryImageFormats(ctx->display, formats->entries,
                                          &formats->num);
    if (!CHECK_VA_STATUS(ctx, "vaQueryImageFormats()"))
        return;
    MP_VERBOSE(ctx, "%d image formats available:\n", formats->num);
    for (int i = 0; i < formats->num; i++)
        MP_VERBOSE(ctx, "  %s\n", mp_tag_str(formats->entries[i].fourcc));
    ctx->image_formats = formats;
}