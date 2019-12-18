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
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  Anime_LoadInfo () ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  GdipLoadImageFromFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int GetFileAttributesW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetZoom () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hDispWnd ; 
 int /*<<< orphan*/  image ; 

__attribute__((used)) static void pLoadImage(LPWSTR szOpenFileName)
{
    /* check file presence */
    if (GetFileAttributesW(szOpenFileName) == 0xFFFFFFFF)
    {
        DPRINT1("File %s not found!\n", szOpenFileName);
        return;
    }

    /* load now */
    GdipLoadImageFromFile(szOpenFileName, &image);
    if (!image)
    {
        DPRINT1("GdipLoadImageFromFile() failed\n");
        return;
    }
    Anime_LoadInfo();

    /* reset zoom */
    ResetZoom();

    /* redraw */
    InvalidateRect(hDispWnd, NULL, TRUE);
}