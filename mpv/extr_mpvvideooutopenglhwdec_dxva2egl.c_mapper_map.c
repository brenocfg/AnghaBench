#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ra_hwdec_mapper {TYPE_1__* src; int /*<<< orphan*/  ra; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  egl_surface; int /*<<< orphan*/  egl_display; int /*<<< orphan*/  gl_texture; int /*<<< orphan*/  query9; int /*<<< orphan*/  surface9; int /*<<< orphan*/  device9ex; } ;
typedef  int int64_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {scalar_t__* planes; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  IDirect3DSurface9 ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_3__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  D3DGETDATA_FLUSH ; 
 int /*<<< orphan*/  D3DISSUE_END ; 
 int /*<<< orphan*/  D3DTEXF_NONE ; 
 int /*<<< orphan*/  EGL_BACK_BUFFER ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 scalar_t__ IDirect3DDevice9Ex_StretchRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirect3DQuery9_GetData (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirect3DQuery9_Issue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_ERR (struct ra_hwdec_mapper*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ra_hwdec_mapper*,char*,long long) ; 
 scalar_t__ S_FALSE ; 
 int /*<<< orphan*/  eglBindTexImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (scalar_t__) ; 
 int /*<<< orphan*/  mp_sleep_us (int const) ; 
 TYPE_3__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mapper_map(struct ra_hwdec_mapper *mapper)
{
    struct priv *p = mapper->priv;
    GL *gl = ra_gl_get(mapper->ra);

    HRESULT hr;
    RECT rc = {0, 0, mapper->src->w, mapper->src->h};
    IDirect3DSurface9* hw_surface = (IDirect3DSurface9 *)mapper->src->planes[3];
    hr = IDirect3DDevice9Ex_StretchRect(p->device9ex,
                                        hw_surface, &rc,
                                        p->surface9, &rc,
                                        D3DTEXF_NONE);
    if (FAILED(hr)) {
        MP_ERR(mapper, "Direct3D RGB conversion failed: %s\n",
               mp_HRESULT_to_str(hr));
        return -1;
    }

    hr = IDirect3DQuery9_Issue(p->query9, D3DISSUE_END);
    if (FAILED(hr)) {
        MP_ERR(mapper, "Failed to issue Direct3D END query\n");
        return -1;
    }

    // There doesn't appear to be an efficient way to do a blocking flush
    // of the above StretchRect. Timeout of 8ms is required to reliably
    // render 4k on Intel Haswell, Ivybridge and Cherry Trail Atom.
    const int max_retries = 8;
    const int64_t wait_us = 1000;
    int retries = 0;
    while (true) {
        hr = IDirect3DQuery9_GetData(p->query9, NULL, 0, D3DGETDATA_FLUSH);
        if (FAILED(hr)) {
            MP_ERR(mapper, "Failed to query Direct3D flush state\n");
            return -1;
        } else if (hr == S_FALSE) {
            if (++retries > max_retries) {
                MP_VERBOSE(mapper, "Failed to flush frame after %lld ms\n",
                           (long long)(wait_us * max_retries) / 1000);
                break;
            }
            mp_sleep_us(wait_us);
        } else {
            break;
        }
    }

    gl->BindTexture(GL_TEXTURE_2D, p->gl_texture);
    eglBindTexImage(p->egl_display, p->egl_surface, EGL_BACK_BUFFER);
    gl->BindTexture(GL_TEXTURE_2D, 0);

    return 0;
}