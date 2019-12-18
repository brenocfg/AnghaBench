#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  texthost; } ;
struct TYPE_6__ {int cbSize; int dwMask; int sStyle; int /*<<< orphan*/  wAlignment; int /*<<< orphan*/  bOutlineLevel; } ;
typedef  TYPE_1__ PARAFORMAT2 ;
typedef  int /*<<< orphan*/  PARAFORMAT ;
typedef  TYPE_2__ ME_TextEditor ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ITextHost_OnTxParaFormatChange (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextHost_TxGetParaFormat (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  PFA_LEFT ; 
 int PFM_ALIGNMENT ; 
 int PFM_ALL2 ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 

void ME_SetDefaultParaFormat(ME_TextEditor *editor, PARAFORMAT2 *pFmt)
{
    const PARAFORMAT2 *host_fmt;
    HRESULT hr;

    ZeroMemory(pFmt, sizeof(PARAFORMAT2));
    pFmt->cbSize = sizeof(PARAFORMAT2);
    pFmt->dwMask = PFM_ALL2;
    pFmt->wAlignment = PFA_LEFT;
    pFmt->sStyle = -1;
    pFmt->bOutlineLevel = TRUE;

    hr = ITextHost_TxGetParaFormat( editor->texthost, (const PARAFORMAT **)&host_fmt );
    if (SUCCEEDED(hr))
    {
        /* Just use the alignment for now */
        if (host_fmt->dwMask & PFM_ALIGNMENT)
            pFmt->wAlignment = host_fmt->wAlignment;
        ITextHost_OnTxParaFormatChange( editor->texthost, (PARAFORMAT *)pFmt );
    }
}