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
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  HENHMETAFILE ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CF_ENHMETAFILE ; 
 int /*<<< orphan*/  GetClipboardData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PlayEnhMetaFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

void PlayEnhMetaFileFromClipboard(HDC hdc, const RECT *lpRect)
{
    HENHMETAFILE hEmf;

    hEmf = GetClipboardData(CF_ENHMETAFILE);
    PlayEnhMetaFile(hdc, hEmf, lpRect);
}