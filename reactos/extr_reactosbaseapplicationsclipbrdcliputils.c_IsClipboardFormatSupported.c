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
typedef  int UINT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  CF_BITMAP 137 
#define  CF_DIB 136 
#define  CF_DIBV5 135 
#define  CF_ENHMETAFILE 134 
#define  CF_HDROP 133 
#define  CF_METAFILEPICT 132 
#define  CF_OEMTEXT 131 
#define  CF_OWNERDISPLAY 130 
#define  CF_TEXT 129 
#define  CF_UNICODETEXT 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOL IsClipboardFormatSupported(UINT uFormat)
{
    switch (uFormat)
    {
        case CF_OWNERDISPLAY:
        case CF_UNICODETEXT:
        case CF_TEXT:
        case CF_OEMTEXT:
        case CF_BITMAP:
        case CF_ENHMETAFILE:
        case CF_METAFILEPICT:
        case CF_DIB:
        case CF_DIBV5:
        case CF_HDROP:
        {
            return TRUE;
        }

        default:
        {
            return FALSE;
        }
    }
}