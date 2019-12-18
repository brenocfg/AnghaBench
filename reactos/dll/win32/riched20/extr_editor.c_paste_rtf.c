#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  pfnCallback; scalar_t__ dwCookie; } ;
struct TYPE_10__ {scalar_t__ nLength; int /*<<< orphan*/  hData; } ;
struct TYPE_8__ {int /*<<< orphan*/  hGlobal; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
typedef  TYPE_2__ STGMEDIUM ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_3__ ME_GlobalDestStruct ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FORMATETC ;
typedef  TYPE_4__ EDITSTREAM ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ME_ReadFromHGLOBALRTF ; 
 scalar_t__ ME_StreamIn (int /*<<< orphan*/ *,int,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseStgMedium (TYPE_2__*) ; 
 int SFF_SELECTION ; 
 int SF_RTF ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT paste_rtf(ME_TextEditor *editor, FORMATETC *fmt, STGMEDIUM *med)
{
    EDITSTREAM es;
    ME_GlobalDestStruct gds;
    HRESULT hr;

    gds.hData = med->u.hGlobal;
    gds.nLength = 0;
    es.dwCookie = (DWORD_PTR)&gds;
    es.pfnCallback = ME_ReadFromHGLOBALRTF;
    hr = ME_StreamIn( editor, SF_RTF | SFF_SELECTION, &es, FALSE ) == 0 ? E_FAIL : S_OK;
    ReleaseStgMedium( med );
    return hr;
}