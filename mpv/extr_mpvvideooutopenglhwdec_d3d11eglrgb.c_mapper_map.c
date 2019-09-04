#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ra_tex_params {int dimensions; int d; int render_src; int src_linear; int /*<<< orphan*/  format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_10__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct ra_hwdec_mapper {int /*<<< orphan*/ * tex; int /*<<< orphan*/  ra; TYPE_3__ src_params; TYPE_2__* src; struct priv* priv; TYPE_1__* owner; } ;
struct priv_owner {int /*<<< orphan*/  egl_display; int /*<<< orphan*/  egl_config; } ;
struct priv {scalar_t__ egl_surface; int /*<<< orphan*/  gl_texture; } ;
struct TYPE_12__ {int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {scalar_t__* planes; } ;
struct TYPE_8__ {struct priv_owner* priv; } ;
typedef  int /*<<< orphan*/  IDXGIResource ;
typedef  int /*<<< orphan*/  ID3D11Texture2D ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  TYPE_4__ GL ;
typedef  int /*<<< orphan*/  EGLint ;
typedef  TYPE_5__ D3D11_TEXTURE2D_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_BACK_BUFFER ; 
 int /*<<< orphan*/  EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE ; 
 int /*<<< orphan*/  EGL_HEIGHT ; 
 int /*<<< orphan*/  EGL_NONE ; 
 scalar_t__ EGL_NO_SURFACE ; 
 int /*<<< orphan*/  EGL_TEXTURE_2D ; 
 int /*<<< orphan*/  EGL_TEXTURE_FORMAT ; 
 int /*<<< orphan*/  EGL_TEXTURE_RGBA ; 
 int /*<<< orphan*/  EGL_TEXTURE_TARGET ; 
 int /*<<< orphan*/  EGL_WIDTH ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  ID3D11Texture2D_GetDesc (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  IDXGIResource_GetSharedHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDXGIResource_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDXGIResource ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  MP_ERR (struct ra_hwdec_mapper*,char*) ; 
 int /*<<< orphan*/  eglBindTexImage (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ eglCreatePbufferFromClientBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_create_wrapped_tex (int /*<<< orphan*/ ,struct ra_tex_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_find_unorm_format (int /*<<< orphan*/ ,int,int) ; 
 TYPE_4__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mapper_map(struct ra_hwdec_mapper *mapper)
{
    struct priv_owner *o = mapper->owner->priv;
    struct priv *p = mapper->priv;
    GL *gl = ra_gl_get(mapper->ra);
    HRESULT hr;

    if (!p->gl_texture)
        return -1;

    ID3D11Texture2D *d3d_tex = (void *)mapper->src->planes[0];
    if (!d3d_tex)
        return -1;

    IDXGIResource *res;
    hr = IUnknown_QueryInterface(d3d_tex, &IID_IDXGIResource, (void **)&res);
    if (FAILED(hr))
        return -1;

    HANDLE share_handle = NULL;
    hr = IDXGIResource_GetSharedHandle(res, &share_handle);
    if (FAILED(hr))
        share_handle = NULL;

    IDXGIResource_Release(res);

    if (!share_handle)
        return -1;

    D3D11_TEXTURE2D_DESC texdesc;
    ID3D11Texture2D_GetDesc(d3d_tex, &texdesc);

    EGLint attrib_list[] = {
        EGL_WIDTH, texdesc.Width,
        EGL_HEIGHT, texdesc.Height,
        EGL_TEXTURE_FORMAT, EGL_TEXTURE_RGBA,
        EGL_TEXTURE_TARGET, EGL_TEXTURE_2D,
        EGL_NONE
    };
    p->egl_surface = eglCreatePbufferFromClientBuffer(
        o->egl_display, EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE,
        share_handle, o->egl_config, attrib_list);
    if (p->egl_surface == EGL_NO_SURFACE) {
        MP_ERR(mapper, "Failed to create EGL surface\n");
        return -1;
    }

    gl->BindTexture(GL_TEXTURE_2D, p->gl_texture);
    eglBindTexImage(o->egl_display, p->egl_surface, EGL_BACK_BUFFER);
    gl->BindTexture(GL_TEXTURE_2D, 0);

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

    mapper->tex[0] = ra_create_wrapped_tex(mapper->ra, &params, p->gl_texture);
    if (!mapper->tex[0])
        return -1;

    return 0;
}