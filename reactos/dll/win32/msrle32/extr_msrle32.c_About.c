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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  CodecInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ICERR_OK ; 
 int /*<<< orphan*/  IDS_ABOUT ; 
 int /*<<< orphan*/  IDS_NAME ; 
 int /*<<< orphan*/  LoadStringW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MB_ICONINFORMATION ; 
 int MB_OK ; 
 scalar_t__ MSRLE32_hModule ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static LRESULT About(CodecInfo *pi, HWND hWnd)
{
  WCHAR szTitle[20];
  WCHAR szAbout[128];

  /* pre-condition */
  assert(MSRLE32_hModule != 0);

  LoadStringW(MSRLE32_hModule, IDS_NAME, szTitle, ARRAY_SIZE(szTitle));
  LoadStringW(MSRLE32_hModule, IDS_ABOUT, szAbout, ARRAY_SIZE(szAbout));

  MessageBoxW(hWnd, szAbout, szTitle, MB_OK|MB_ICONINFORMATION);

  return ICERR_OK;
}