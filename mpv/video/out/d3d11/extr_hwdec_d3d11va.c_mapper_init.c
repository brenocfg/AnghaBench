#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ra_imgfmt_desc {int num_planes; int /*<<< orphan*/ * planes; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {int imgfmt; int hw_subfmt; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct ra_hwdec_mapper {int /*<<< orphan*/ * tex; int /*<<< orphan*/  ra; TYPE_5__ dst_params; TYPE_5__ src_params; struct priv* priv; TYPE_1__* owner; } ;
struct priv_owner {int /*<<< orphan*/  device1; int /*<<< orphan*/  device; TYPE_2__* opts; } ;
struct priv {int num_planes; int /*<<< orphan*/  ctx; int /*<<< orphan*/  copy_tex; int /*<<< orphan*/ * fmt; } ;
struct mp_image {int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int Count; } ;
struct TYPE_10__ {int MipLevels; int ArraySize; int /*<<< orphan*/  BindFlags; int /*<<< orphan*/  Format; TYPE_3__ SampleDesc; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;
struct TYPE_8__ {scalar_t__ zero_copy; } ;
struct TYPE_7__ {struct priv_owner* priv; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DXGI_FORMAT ;
typedef  TYPE_4__ D3D11_TEXTURE2D_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_BIND_SHADER_RESOURCE ; 
 int /*<<< orphan*/  DXGI_FORMAT_NV12 ; 
 int /*<<< orphan*/  DXGI_FORMAT_P010 ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11Device1_GetImmediateContext1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Device_CreateTexture2D (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  IMGFMT_NV12 129 
#define  IMGFMT_P010 128 
 int /*<<< orphan*/  MP_FATAL (struct ra_hwdec_mapper*,char*) ; 
 int /*<<< orphan*/  mp_image_plane_h (struct mp_image*,int) ; 
 int /*<<< orphan*/  mp_image_plane_w (struct mp_image*,int) ; 
 int /*<<< orphan*/  mp_image_set_params (struct mp_image*,TYPE_5__*) ; 
 int /*<<< orphan*/  ra_d3d11_wrap_tex_video (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_get_imgfmt_desc (int /*<<< orphan*/ ,int,struct ra_imgfmt_desc*) ; 

__attribute__((used)) static int mapper_init(struct ra_hwdec_mapper *mapper)
{
    struct priv_owner *o = mapper->owner->priv;
    struct priv *p = mapper->priv;
    HRESULT hr;

    mapper->dst_params = mapper->src_params;
    mapper->dst_params.imgfmt = mapper->src_params.hw_subfmt;
    mapper->dst_params.hw_subfmt = 0;

    struct ra_imgfmt_desc desc = {0};

    if (!ra_get_imgfmt_desc(mapper->ra, mapper->dst_params.imgfmt, &desc))
        return -1;

    if (o->opts->zero_copy) {
        // In the zero-copy path, we create the ra_tex objects in the map
        // operation, so we just need to store the format of each plane
        p->num_planes = desc.num_planes;
        for (int i = 0; i < desc.num_planes; i++)
            p->fmt[i] = desc.planes[i];
    } else {
        struct mp_image layout = {0};
        mp_image_set_params(&layout, &mapper->dst_params);

        DXGI_FORMAT copy_fmt;
        switch (mapper->dst_params.imgfmt) {
        case IMGFMT_NV12: copy_fmt = DXGI_FORMAT_NV12; break;
        case IMGFMT_P010: copy_fmt = DXGI_FORMAT_P010; break;
        default: return -1;
        }

        D3D11_TEXTURE2D_DESC copy_desc = {
            .Width = mapper->dst_params.w,
            .Height = mapper->dst_params.h,
            .MipLevels = 1,
            .ArraySize = 1,
            .SampleDesc.Count = 1,
            .Format = copy_fmt,
            .BindFlags = D3D11_BIND_SHADER_RESOURCE,
        };
        hr = ID3D11Device_CreateTexture2D(o->device, &copy_desc, NULL,
                                          &p->copy_tex);
        if (FAILED(hr)) {
            MP_FATAL(mapper, "Could not create shader resource texture\n");
            return -1;
        }

        for (int i = 0; i < desc.num_planes; i++) {
            mapper->tex[i] = ra_d3d11_wrap_tex_video(mapper->ra, p->copy_tex,
                mp_image_plane_w(&layout, i), mp_image_plane_h(&layout, i), 0,
                desc.planes[i]);
            if (!mapper->tex[i]) {
                MP_FATAL(mapper, "Could not create RA texture view\n");
                return -1;
            }
        }

        // A ref to the immediate context is needed for CopySubresourceRegion
        ID3D11Device1_GetImmediateContext1(o->device1, &p->ctx);
    }

    return 0;
}