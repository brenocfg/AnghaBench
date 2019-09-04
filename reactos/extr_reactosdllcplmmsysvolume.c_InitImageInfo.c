#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {int /*<<< orphan*/  bmHeight; int /*<<< orphan*/  bmWidth; } ;
struct TYPE_6__ {int /*<<< orphan*/  cySource; int /*<<< orphan*/  cxSource; int /*<<< orphan*/ * hBitmap; } ;
typedef  TYPE_1__* PIMGINFO ;
typedef  TYPE_2__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  GetObject (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  IDB_SPEAKIMG ; 
 int /*<<< orphan*/  IMAGE_BITMAP ; 
 int /*<<< orphan*/  LR_DEFAULTCOLOR ; 
 int /*<<< orphan*/ * LoadImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hApplet ; 

__attribute__((used)) static VOID
InitImageInfo(PIMGINFO ImgInfo)
{
    BITMAP bitmap;

    ZeroMemory(ImgInfo, sizeof(*ImgInfo));

    ImgInfo->hBitmap = LoadImage(hApplet,
                                 MAKEINTRESOURCE(IDB_SPEAKIMG),
                                 IMAGE_BITMAP,
                                 0,
                                 0,
                                 LR_DEFAULTCOLOR);

    if (ImgInfo->hBitmap != NULL)
    {
        GetObject(ImgInfo->hBitmap, sizeof(BITMAP), &bitmap);

        ImgInfo->cxSource = bitmap.bmWidth;
        ImgInfo->cySource = bitmap.bmHeight;
    }
}