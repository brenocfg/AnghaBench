#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ra_ctx {int /*<<< orphan*/  vo; struct priv* priv; } ;
struct priv {scalar_t__ hdc; } ;
struct TYPE_5__ {int nSize; int nVersion; int dwFlags; int cColorBits; int /*<<< orphan*/  iLayerType; int /*<<< orphan*/  iPixelType; } ;
typedef  TYPE_1__ PIXELFORMATDESCRIPTOR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HDC ;

/* Variables and functions */
 int ChoosePixelFormat (scalar_t__,TYPE_1__*) ; 
 scalar_t__ GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_ERR (int /*<<< orphan*/ ,char*) ; 
 int PFD_DOUBLEBUFFER ; 
 int PFD_DRAW_TO_WINDOW ; 
 int /*<<< orphan*/  PFD_MAIN_PLANE ; 
 int PFD_SUPPORT_OPENGL ; 
 int /*<<< orphan*/  PFD_TYPE_RGBA ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetPixelFormat (scalar_t__,int,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vo_w32_hwnd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool create_dc(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    HWND win = vo_w32_hwnd(ctx->vo);

    if (p->hdc)
        return true;

    HDC hdc = GetDC(win);
    if (!hdc)
        return false;

    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof pfd);
    pfd.nSize = sizeof pfd;
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;
    int pf = ChoosePixelFormat(hdc, &pfd);

    if (!pf) {
        MP_ERR(ctx->vo, "unable to select a valid pixel format!\n");
        ReleaseDC(win, hdc);
        return false;
    }

    SetPixelFormat(hdc, pf, &pfd);

    p->hdc = hdc;
    return true;
}