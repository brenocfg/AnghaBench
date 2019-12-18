#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szTitleBuf ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  FileName; } ;
typedef  TYPE_1__ SHIMGVW_FILENODE ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (scalar_t__) ; 
 int /*<<< orphan*/  IDS_APPTITLE ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StringCbPrintfW (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hInstance ; 
 scalar_t__ image ; 
 int /*<<< orphan*/  pLoadImage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wcsrchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static VOID
pLoadImageFromNode(SHIMGVW_FILENODE *node, HWND hwnd)
{
    WCHAR szTitleBuf[800];
    WCHAR szResStr[512];
    WCHAR *c;

    if (node)
    {
        c = wcsrchr(node->FileName, '\\');
        if (c)
        {
            c++;
        }

        LoadStringW(hInstance, IDS_APPTITLE, szResStr, ARRAYSIZE(szResStr));
        StringCbPrintfW(szTitleBuf, sizeof(szTitleBuf), L"%ls%ls%ls", szResStr, L" - ", c);
        SetWindowTextW(hwnd, szTitleBuf);

        if (image)
        {
            GdipDisposeImage(image);
        }

        pLoadImage(node->FileName);
    }
}