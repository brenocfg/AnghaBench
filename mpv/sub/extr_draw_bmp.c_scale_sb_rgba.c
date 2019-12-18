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
struct sub_bitmap {int /*<<< orphan*/  dh; int /*<<< orphan*/  dw; int /*<<< orphan*/  stride; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_2__ {int /*<<< orphan*/  color; } ;
struct mp_image {TYPE_1__ params; int /*<<< orphan*/  imgfmt; int /*<<< orphan*/ * stride; int /*<<< orphan*/ * planes; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMGFMT_BGR32 ; 
 int /*<<< orphan*/  IMGFMT_Y8 ; 
 int /*<<< orphan*/  SWS_BILINEAR ; 
 struct mp_image* mp_image_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_set_size (struct mp_image*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_setfmt (struct mp_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_swscale (struct mp_image*,struct mp_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 
 int /*<<< orphan*/  unpremultiply_and_split_BGR32 (struct mp_image*,struct mp_image*) ; 

__attribute__((used)) static void scale_sb_rgba(struct sub_bitmap *sb, const struct mp_image *dst_format,
                          struct mp_image **out_sbi, struct mp_image **out_sba)
{
    struct mp_image sbisrc = {0};
    mp_image_setfmt(&sbisrc, IMGFMT_BGR32);
    mp_image_set_size(&sbisrc, sb->w, sb->h);
    sbisrc.planes[0] = sb->bitmap;
    sbisrc.stride[0] = sb->stride;
    struct mp_image *sbisrc2 = mp_image_alloc(IMGFMT_BGR32, sb->dw, sb->dh);
    struct mp_image *sba = mp_image_alloc(IMGFMT_Y8, sb->dw, sb->dh);
    struct mp_image *sbi = mp_image_alloc(dst_format->imgfmt, sb->dw, sb->dh);
    if (!sbisrc2 || !sba || !sbi) {
        talloc_free(sbisrc2);
        talloc_free(sba);
        talloc_free(sbi);
        return;
    }

    mp_image_swscale(sbisrc2, &sbisrc, SWS_BILINEAR);
    unpremultiply_and_split_BGR32(sbisrc2, sba);

    sbi->params.color = dst_format->params.color;
    mp_image_swscale(sbi, sbisrc2, SWS_BILINEAR);

    talloc_free(sbisrc2);

    *out_sbi = sbi;
    *out_sba = sba;
}