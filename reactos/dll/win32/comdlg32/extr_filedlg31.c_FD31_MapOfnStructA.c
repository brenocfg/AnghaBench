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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_9__ {int nMaxFile; int nMaxFileTitle; int Flags; scalar_t__ lStructSize; int /*<<< orphan*/  FlagsEx; int /*<<< orphan*/  dwReserved; int /*<<< orphan*/  pvReserved; int /*<<< orphan*/  lpTemplateName; void* lpstrDefExt; int /*<<< orphan*/  nFileExtension; int /*<<< orphan*/  nFileOffset; int /*<<< orphan*/  lpstrTitle; int /*<<< orphan*/  lpstrInitialDir; void* lpstrFileTitle; void* lpstrFile; int /*<<< orphan*/  nFilterIndex; scalar_t__ nMaxCustFilter; void* lpstrCustomFilter; void* lpstrFilter; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  hwndOwner; } ;
struct TYPE_8__ {int nMaxFile; int nMaxFileTitle; int Flags; int /*<<< orphan*/  FlagsEx; int /*<<< orphan*/  dwReserved; int /*<<< orphan*/  pvReserved; scalar_t__ lpTemplateName; int /*<<< orphan*/  lpstrDefExt; int /*<<< orphan*/  nFileExtension; int /*<<< orphan*/  nFileOffset; scalar_t__ lpstrTitle; scalar_t__ lpstrInitialDir; int /*<<< orphan*/  lpstrFileTitle; int /*<<< orphan*/  lpstrFile; int /*<<< orphan*/  nFilterIndex; scalar_t__ nMaxCustFilter; scalar_t__* lpstrCustomFilter; scalar_t__* lpstrFilter; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  hwndOwner; } ;
typedef  TYPE_2__ OPENFILENAMEA ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  TYPE_3__* LPOPENFILENAMEW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COMDLG32_hInstance ; 
 void* FD31_DupToW (int /*<<< orphan*/ ,int) ; 
 void* FD31_MapStringPairsToW (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  IDS_OPEN_FILE ; 
 int /*<<< orphan*/  IDS_SAVE_AS ; 
 int /*<<< orphan*/  IS_INTRESOURCE (scalar_t__) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int OFN_ENABLETEMPLATE ; 
 scalar_t__ OPENFILENAME_SIZE_VERSION_400W ; 
 int /*<<< orphan*/  RtlCreateUnicodeStringFromAsciiz (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  heap_alloc (int) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void FD31_MapOfnStructA(const OPENFILENAMEA *ofnA, LPOPENFILENAMEW ofnW, BOOL open)
{
    UNICODE_STRING usBuffer;

    ofnW->hwndOwner = ofnA->hwndOwner;
    ofnW->hInstance = ofnA->hInstance;
    if (ofnA->lpstrFilter)
        ofnW->lpstrFilter = FD31_MapStringPairsToW(ofnA->lpstrFilter, 0);

    if ((ofnA->lpstrCustomFilter) && (*(ofnA->lpstrCustomFilter)))
        ofnW->lpstrCustomFilter = FD31_MapStringPairsToW(ofnA->lpstrCustomFilter, ofnA->nMaxCustFilter);
    ofnW->nMaxCustFilter = ofnA->nMaxCustFilter;
    ofnW->nFilterIndex = ofnA->nFilterIndex;
    ofnW->nMaxFile = ofnA->nMaxFile;
    ofnW->lpstrFile = FD31_DupToW(ofnA->lpstrFile, ofnW->nMaxFile);
    ofnW->nMaxFileTitle = ofnA->nMaxFileTitle;
    ofnW->lpstrFileTitle = FD31_DupToW(ofnA->lpstrFileTitle, ofnW->nMaxFileTitle);
    if (ofnA->lpstrInitialDir)
    {
        RtlCreateUnicodeStringFromAsciiz (&usBuffer,ofnA->lpstrInitialDir);
        ofnW->lpstrInitialDir = usBuffer.Buffer;
    }
    if (ofnA->lpstrTitle) {
        RtlCreateUnicodeStringFromAsciiz (&usBuffer, ofnA->lpstrTitle);
        ofnW->lpstrTitle = usBuffer.Buffer;
    } else {
        WCHAR buf[16];
        LPWSTR title_tmp;
        int len;
        LoadStringW(COMDLG32_hInstance, open ? IDS_OPEN_FILE : IDS_SAVE_AS, buf, ARRAY_SIZE(buf));
        len = lstrlenW(buf)+1;
        title_tmp = heap_alloc(len * sizeof(WCHAR));
        memcpy(title_tmp, buf, len * sizeof(WCHAR));
        ofnW->lpstrTitle = title_tmp;
    }
    ofnW->Flags = ofnA->Flags;
    ofnW->nFileOffset = ofnA->nFileOffset;
    ofnW->nFileExtension = ofnA->nFileExtension;
    ofnW->lpstrDefExt = FD31_DupToW(ofnA->lpstrDefExt, 3);
    if ((ofnA->Flags & OFN_ENABLETEMPLATE) && (ofnA->lpTemplateName))
    {
        if (!IS_INTRESOURCE(ofnA->lpTemplateName))
        {
            RtlCreateUnicodeStringFromAsciiz (&usBuffer,ofnA->lpTemplateName);
            ofnW->lpTemplateName = usBuffer.Buffer;
        }
        else /* numbered resource */
            ofnW->lpTemplateName = (LPCWSTR) ofnA->lpTemplateName;
    }
    if (ofnW->lStructSize > OPENFILENAME_SIZE_VERSION_400W)
    {
        ofnW->pvReserved = ofnA->pvReserved;
        ofnW->dwReserved = ofnA->dwReserved;
        ofnW->FlagsEx    = ofnA->FlagsEx;
    }
}