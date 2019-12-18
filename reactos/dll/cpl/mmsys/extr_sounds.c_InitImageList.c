#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ UINT ;
typedef  int INT ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int ILC_COLOR32 ; 
 int ILC_MASK ; 
 int /*<<< orphan*/  IMAGE_BITMAP ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 int ImageList_AddIcon (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ImageList_AddMasked (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ImageList_Create (scalar_t__,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ImageList_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LR_LOADTRANSPARENT ; 
 int /*<<< orphan*/ * LoadImageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (scalar_t__) ; 
 int /*<<< orphan*/  RGB (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hApplet ; 

HIMAGELIST
InitImageList(UINT StartResource,
              UINT EndResource,
              UINT Width,
              UINT Height,
              ULONG type)
{
    HANDLE hImage;
    HIMAGELIST himl;
    UINT i;
    INT ret;

    /* Create the toolbar icon image list */
    himl = ImageList_Create(Width,
                            Height,
                            ILC_MASK | ILC_COLOR32,
                            EndResource - StartResource,
                            0);
    if (himl == NULL)
        return NULL;

    ret = 0;
    for (i = StartResource; i <= EndResource && ret != -1; i++)
    {
        hImage = LoadImageW(hApplet,
                            MAKEINTRESOURCEW(i),
                            type,
                            Width,
                            Height,
                            LR_LOADTRANSPARENT);
        if (hImage == NULL)
        {
            ImageList_Destroy(himl);
            himl = NULL;
            break;
        }

        if (type == IMAGE_BITMAP)
        {
            ret = ImageList_AddMasked(himl,
                                      hImage,
                                      RGB(255, 0, 128));
        }
        else if (type == IMAGE_ICON)
        {
            ret = ImageList_AddIcon(himl,
                                    hImage);
        }

        DeleteObject(hImage);
    }

    if (ret == -1)
    {
        ImageList_Destroy(himl);
        himl = NULL;
    }

    return himl;
}