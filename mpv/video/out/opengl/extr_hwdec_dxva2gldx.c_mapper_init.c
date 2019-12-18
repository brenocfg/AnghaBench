#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ra_tex_params {int dimensions; int d; int render_src; int src_linear; int /*<<< orphan*/  format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_6__ {scalar_t__ hw_subfmt; int /*<<< orphan*/  imgfmt; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct ra_hwdec_mapper {TYPE_2__ dst_params; TYPE_2__ src_params; int /*<<< orphan*/ * tex; int /*<<< orphan*/  ra; struct priv* priv; TYPE_1__* owner; } ;
struct priv_owner {int /*<<< orphan*/  device_h; int /*<<< orphan*/  device; } ;
struct priv {int /*<<< orphan*/  texture; int /*<<< orphan*/  rtarget_h; int /*<<< orphan*/  device_h; int /*<<< orphan*/  rtarget; int /*<<< orphan*/  device; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* DXLockObjectsNV ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* DXRegisterObjectNV ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* TexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GenTextures ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* DXSetResourceShareHandleNV ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {struct priv_owner* priv; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  TYPE_3__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  D3DMULTISAMPLE_NONE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 int /*<<< orphan*/  IDirect3DDevice9Ex_CreateRenderTarget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IMGFMT_RGB0 ; 
 int /*<<< orphan*/  MP_ERR (struct ra_hwdec_mapper*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHARED_SURFACE_D3DFMT ; 
 int /*<<< orphan*/  WGL_ACCESS_READ_ONLY_NV ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_LastError_to_str () ; 
 int /*<<< orphan*/  ra_create_wrapped_tex (int /*<<< orphan*/ ,struct ra_tex_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_find_unorm_format (int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mapper_init(struct ra_hwdec_mapper *mapper)
{
    struct priv_owner *p_owner = mapper->owner->priv;
    struct priv *p = mapper->priv;
    GL *gl = ra_gl_get(mapper->ra);
    HRESULT hr;

    p->device = p_owner->device;
    p->device_h = p_owner->device_h;

    HANDLE share_handle = NULL;
    hr = IDirect3DDevice9Ex_CreateRenderTarget(
        p->device,
        mapper->src_params.w, mapper->src_params.h,
        SHARED_SURFACE_D3DFMT, D3DMULTISAMPLE_NONE, 0, FALSE,
        &p->rtarget, &share_handle);
    if (FAILED(hr)) {
        MP_ERR(mapper, "Failed creating offscreen Direct3D surface: %s\n",
               mp_HRESULT_to_str(hr));
        return -1;
    }

    if (share_handle &&
        !gl->DXSetResourceShareHandleNV(p->rtarget, share_handle)) {
        MP_ERR(mapper, "Failed setting Direct3D/OpenGL share handle for surface: %s\n",
               mp_LastError_to_str());
        return -1;
    }

    gl->GenTextures(1, &p->texture);
    gl->BindTexture(GL_TEXTURE_2D, p->texture);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    gl->BindTexture(GL_TEXTURE_2D, 0);

    p->rtarget_h = gl->DXRegisterObjectNV(p->device_h, p->rtarget, p->texture,
                                          GL_TEXTURE_2D,
                                          WGL_ACCESS_READ_ONLY_NV);
    if (!p->rtarget_h) {
        MP_ERR(mapper, "Failed to register Direct3D surface with OpenGL: %s\n",
               mp_LastError_to_str());
        return -1;
    }

    if (!gl->DXLockObjectsNV(p->device_h, 1, &p->rtarget_h)) {
        MP_ERR(mapper, "Failed locking texture for access by OpenGL %s\n",
               mp_LastError_to_str());
        return -1;
    }

    struct ra_tex_params params = {
        .dimensions = 2,
        .w = mapper->src_params.w,
        .h = mapper->src_params.h,
        .d = 1,
        .format = ra_find_unorm_format(mapper->ra, 1, 4),
        .render_src = true,
        .src_linear = true,
    };
    if (!params.format)
        return -1;

    mapper->tex[0] = ra_create_wrapped_tex(mapper->ra, &params, p->texture);
    if (!mapper->tex[0])
        return -1;

    mapper->dst_params = mapper->src_params;
    mapper->dst_params.imgfmt = IMGFMT_RGB0;
    mapper->dst_params.hw_subfmt = 0;

    return 0;
}