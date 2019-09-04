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
struct sub_bitmaps {int dummy; } ;
struct osd_state {int dummy; } ;
struct osd_object {scalar_t__ type; int num_externals; int changed; int /*<<< orphan*/ * ass_imgs; scalar_t__ ass_packer; int /*<<< orphan*/  vo_res; TYPE_1__* externals; int /*<<< orphan*/  ass; scalar_t__ osd_changed; } ;
struct TYPE_2__ {int /*<<< orphan*/  ass; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_GROW (struct osd_object*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ OSDTYPE_OSD ; 
 int /*<<< orphan*/  append_ass (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ mp_ass_packer_alloc (struct osd_object*) ; 
 int /*<<< orphan*/  mp_ass_packer_pack (scalar_t__,int /*<<< orphan*/ *,int,int,int,struct sub_bitmaps*) ; 
 int /*<<< orphan*/  update_osd (struct osd_state*,struct osd_object*) ; 

void osd_object_get_bitmaps(struct osd_state *osd, struct osd_object *obj,
                            int format, struct sub_bitmaps *out_imgs)
{
    if (obj->type == OSDTYPE_OSD && obj->osd_changed)
        update_osd(osd, obj);

    if (!obj->ass_packer)
        obj->ass_packer = mp_ass_packer_alloc(obj);

    MP_TARRAY_GROW(obj, obj->ass_imgs, obj->num_externals + 1);

    append_ass(&obj->ass, &obj->vo_res, &obj->ass_imgs[0], &obj->changed);
    for (int n = 0; n < obj->num_externals; n++) {
        append_ass(&obj->externals[n].ass, &obj->vo_res, &obj->ass_imgs[n + 1],
                   &obj->changed);
    }

    mp_ass_packer_pack(obj->ass_packer, obj->ass_imgs, obj->num_externals + 1,
                       obj->changed, format, out_imgs);

    obj->changed = false;
}