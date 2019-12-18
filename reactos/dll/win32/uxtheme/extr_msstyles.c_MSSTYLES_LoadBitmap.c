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
typedef  int /*<<< orphan*/  szFile ;
typedef  char WCHAR ;
struct TYPE_9__ {TYPE_1__* tf; int /*<<< orphan*/  hTheme; } ;
struct TYPE_8__ {int /*<<< orphan*/  image; int /*<<< orphan*/  name; struct TYPE_8__* next; int /*<<< orphan*/  hasAlpha; } ;
struct TYPE_7__ {TYPE_2__* images; } ;
typedef  int /*<<< orphan*/  THEME_IMAGE ;
typedef  TYPE_2__* PTHEME_IMAGE ;
typedef  TYPE_3__* PTHEME_CLASS ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IMAGE_BITMAP ; 
 int /*<<< orphan*/  LR_CREATEDIBSECTION ; 
 int /*<<< orphan*/  LoadImageW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 scalar_t__ lstrcmpiW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lstrcpynW (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prepare_alpha (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HBITMAP MSSTYLES_LoadBitmap (PTHEME_CLASS tc, LPCWSTR lpFilename, BOOL* hasAlpha)
{
    WCHAR szFile[MAX_PATH];
    LPWSTR tmp;
    PTHEME_IMAGE img;
    lstrcpynW(szFile, lpFilename, sizeof(szFile)/sizeof(szFile[0]));
    tmp = szFile;
    do {
        if(*tmp == '\\') *tmp = '_';
        if(*tmp == '/') *tmp = '_';
        if(*tmp == '.') *tmp = '_';
    } while(*tmp++);

    /* Try to locate in list of loaded images */
    img = tc->tf->images;
    while (img)
    {
        if (lstrcmpiW (szFile, img->name) == 0)
        {
            TRACE ("found %p %s: %p\n", img, debugstr_w (img->name), img->image);
            *hasAlpha = img->hasAlpha;
            return img->image;
        }
        img = img->next;
    }
    /* Not found? Load from resources */
    img = HeapAlloc (GetProcessHeap(), 0, sizeof (THEME_IMAGE));
    img->image = LoadImageW(tc->hTheme, szFile, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    prepare_alpha (img->image, hasAlpha);
    img->hasAlpha = *hasAlpha;
    /* ...and stow away for later reuse. */
    lstrcpyW (img->name, szFile);
    img->next = tc->tf->images;
    tc->tf->images = img;
    TRACE ("new %p %s: %p\n", img, debugstr_w (img->name), img->image);
    return img->image;
}