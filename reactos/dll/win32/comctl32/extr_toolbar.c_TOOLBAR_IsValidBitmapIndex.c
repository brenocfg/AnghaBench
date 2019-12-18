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
typedef  int /*<<< orphan*/  TOOLBAR_INFO ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HIMAGELIST ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GETDEFIMAGELIST (int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ GETHIMLID (int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ GETIBITMAP (int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ I_IMAGECALLBACK ; 
 scalar_t__ ImageList_GetImageCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
TOOLBAR_IsValidBitmapIndex(const TOOLBAR_INFO *infoPtr, INT index)
{
    HIMAGELIST himl;
    INT id = GETHIMLID(infoPtr, index);
    INT iBitmap = GETIBITMAP(infoPtr, index);

    if (((himl = GETDEFIMAGELIST(infoPtr, id)) &&
        iBitmap >= 0 && iBitmap < ImageList_GetImageCount(himl)) ||
        (index == I_IMAGECALLBACK))
      return TRUE;
    else
      return FALSE;
}