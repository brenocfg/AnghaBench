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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
#define  CF_BITMAP 141 
#define  CF_DIB 140 
#define  CF_DIBV5 139 
#define  CF_DSPBITMAP 138 
#define  CF_DSPENHMETAFILE 137 
#define  CF_DSPMETAFILEPICT 136 
#define  CF_DSPTEXT 135 
#define  CF_ENHMETAFILE 134 
#define  CF_METAFILEPICT 133 
#define  CF_OEMTEXT 132 
#define  CF_OWNERDISPLAY 131 
#define  CF_PALETTE 130 
#define  CF_TEXT 129 
#define  CF_UNICODETEXT 128 
 int /*<<< orphan*/  GetPriorityClipboardFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

UINT GetAutomaticClipboardFormat(void)
{
    static UINT uFormatList[] =
    {
        CF_OWNERDISPLAY,
        CF_UNICODETEXT,
        CF_TEXT,
        CF_OEMTEXT,
        CF_ENHMETAFILE,
        CF_METAFILEPICT,
        CF_DIBV5,
        CF_DIB,
        CF_BITMAP,
        CF_DSPTEXT,
        CF_DSPBITMAP,
        CF_DSPMETAFILEPICT,
        CF_DSPENHMETAFILE,
        CF_PALETTE
    };

    return GetPriorityClipboardFormat(uFormatList, ARRAYSIZE(uFormatList));
}