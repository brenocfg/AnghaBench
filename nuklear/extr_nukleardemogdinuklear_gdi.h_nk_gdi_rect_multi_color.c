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
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct nk_color {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  memory_dc; int /*<<< orphan*/  window_dc; } ;
struct TYPE_11__ {int /*<<< orphan*/  AlphaFormat; scalar_t__ SourceConstantAlpha; scalar_t__ BlendFlags; int /*<<< orphan*/  BlendOp; } ;
struct TYPE_10__ {int Vertex1; int Vertex2; int Vertex3; } ;
struct TYPE_9__ {short x; short y; } ;
typedef  TYPE_1__ TRIVERTEX ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_2__ GRADIENT_TRIANGLE ;
typedef  int /*<<< orphan*/  GRADIENT_RECT ;
typedef  TYPE_3__ BLENDFUNCTION ;

/* Variables and functions */
 int /*<<< orphan*/  AC_SRC_ALPHA ; 
 int /*<<< orphan*/  AC_SRC_OVER ; 
 int /*<<< orphan*/  AlphaBlend (int /*<<< orphan*/ ,short,short,short,short,int /*<<< orphan*/ ,short,short,short,short,TYPE_3__) ; 
 int /*<<< orphan*/  GRADIENT_FILL_TRIANGLE ; 
 int /*<<< orphan*/  GdiGradientFill (int /*<<< orphan*/ ,TYPE_1__*,int,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 TYPE_5__ gdi ; 
 int /*<<< orphan*/  nk_gdi_set_vertexColor (TYPE_1__*,struct nk_color) ; 

__attribute__((used)) static void
nk_gdi_rect_multi_color(HDC dc, short x, short y, unsigned short w,
    unsigned short h, struct nk_color left, struct nk_color top,
    struct nk_color right, struct nk_color bottom)
{
    BLENDFUNCTION alphaFunction;
    GRADIENT_RECT gRect;
    GRADIENT_TRIANGLE gTri[2];
    TRIVERTEX vt[4];
    alphaFunction.BlendOp = AC_SRC_OVER;
    alphaFunction.BlendFlags = 0;
    alphaFunction.SourceConstantAlpha = 0;
    alphaFunction.AlphaFormat = AC_SRC_ALPHA;

    /* TODO: This Case Needs Repair.*/
    /* Top Left Corner */
    vt[0].x     = x;
    vt[0].y     = y;
    nk_gdi_set_vertexColor(&vt[0], left);
    /* Top Right Corner */
    vt[1].x     = x+w;
    vt[1].y     = y;
    nk_gdi_set_vertexColor(&vt[1], top);
    /* Bottom Left Corner */
    vt[2].x     = x;
    vt[2].y     = y+h;
    nk_gdi_set_vertexColor(&vt[2], right);

    /* Bottom Right Corner */
    vt[3].x     = x+w;
    vt[3].y     = y+h;
    nk_gdi_set_vertexColor(&vt[3], bottom);

    gTri[0].Vertex1 = 0;
    gTri[0].Vertex2 = 1;
    gTri[0].Vertex3 = 2;
    gTri[1].Vertex1 = 2;
    gTri[1].Vertex2 = 1;
    gTri[1].Vertex3 = 3;
    GdiGradientFill(dc, vt, 4, gTri, 2 , GRADIENT_FILL_TRIANGLE);
    AlphaBlend(gdi.window_dc,  x, y, x+w, y+h,gdi.memory_dc, x, y, x+w, y+h,alphaFunction);

}