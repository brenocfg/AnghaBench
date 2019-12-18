#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ra_imgfmt_desc {int /*<<< orphan*/  num_planes; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {scalar_t__ imgfmt; scalar_t__ hw_subfmt; } ;
struct ra_hwdec_mapper {TYPE_3__ dst_params; int /*<<< orphan*/  ra; TYPE_3__ src_params; struct priv* priv; TYPE_1__* owner; } ;
struct priv_owner {int /*<<< orphan*/  probing_formats; int /*<<< orphan*/  (* interop_init ) (struct ra_hwdec_mapper*,struct ra_imgfmt_desc*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  image_id; int /*<<< orphan*/  buf; } ;
struct priv {int /*<<< orphan*/  layout; int /*<<< orphan*/  num_planes; TYPE_2__ current_image; } ;
struct TYPE_4__ {struct priv_owner* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct ra_hwdec_mapper*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VA_INVALID_ID ; 
 int /*<<< orphan*/  check_fmt (struct ra_hwdec_mapper*,scalar_t__) ; 
 int /*<<< orphan*/  mp_image_set_params (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mp_imgfmt_to_name (scalar_t__) ; 
 int /*<<< orphan*/  ra_get_imgfmt_desc (int /*<<< orphan*/ ,scalar_t__,struct ra_imgfmt_desc*) ; 
 int /*<<< orphan*/  stub1 (struct ra_hwdec_mapper*,struct ra_imgfmt_desc*) ; 

__attribute__((used)) static int mapper_init(struct ra_hwdec_mapper *mapper)
{
    struct priv_owner *p_owner = mapper->owner->priv;
    struct priv *p = mapper->priv;

    p->current_image.buf = p->current_image.image_id = VA_INVALID_ID;

    mapper->dst_params = mapper->src_params;
    mapper->dst_params.imgfmt = mapper->src_params.hw_subfmt;
    mapper->dst_params.hw_subfmt = 0;

    struct ra_imgfmt_desc desc = {0};

    if (!ra_get_imgfmt_desc(mapper->ra, mapper->dst_params.imgfmt, &desc))
        return -1;

    p->num_planes = desc.num_planes;
    mp_image_set_params(&p->layout, &mapper->dst_params);

    if (p_owner->interop_init)
        if (!p_owner->interop_init(mapper, &desc))
            return -1;

    if (!p_owner->probing_formats && !check_fmt(mapper, mapper->dst_params.imgfmt))
    {
        MP_FATAL(mapper, "unsupported VA image format %s\n",
                 mp_imgfmt_to_name(mapper->dst_params.imgfmt));
        return -1;
    }

    return 0;
}