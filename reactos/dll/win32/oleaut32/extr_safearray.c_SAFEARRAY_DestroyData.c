#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VARIANT ;
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {int fFeatures; scalar_t__ pvData; scalar_t__ cbElements; } ;
typedef  TYPE_1__ SAFEARRAY ;
typedef  scalar_t__ PBYTE ;
typedef  scalar_t__ LPUNKNOWN ;
typedef  int /*<<< orphan*/  IRecordInfo ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_UNEXPECTED ; 
 int FADF_BSTR ; 
 int FADF_DATADELETED ; 
 int FADF_DISPATCH ; 
 int FADF_RECORD ; 
 int FADF_UNKNOWN ; 
 int FADF_VARIANT ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  IRecordInfo_RecordClear (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  IRecordInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (scalar_t__) ; 
 scalar_t__ SAFEARRAY_GetCellCount (TYPE_1__*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SafeArrayGetRecordInfo (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT SAFEARRAY_DestroyData(SAFEARRAY *psa, ULONG ulStartCell)
{
  if (psa->pvData && !(psa->fFeatures & FADF_DATADELETED))
  {
    ULONG ulCellCount = SAFEARRAY_GetCellCount(psa);

    if (ulStartCell > ulCellCount) {
      FIXME("unexpected ulCellCount %d, start %d\n",ulCellCount,ulStartCell);
      return E_UNEXPECTED;
    }

    ulCellCount -= ulStartCell;

    if (psa->fFeatures & (FADF_UNKNOWN|FADF_DISPATCH))
    {
      LPUNKNOWN *lpUnknown = (LPUNKNOWN *)psa->pvData + ulStartCell;

      while(ulCellCount--)
      {
        if (*lpUnknown)
          IUnknown_Release(*lpUnknown);
        lpUnknown++;
      }
    }
    else if (psa->fFeatures & FADF_RECORD)
    {
      IRecordInfo *lpRecInfo;

      if (SUCCEEDED(SafeArrayGetRecordInfo(psa, &lpRecInfo)))
      {
        PBYTE pRecordData = psa->pvData;
        while(ulCellCount--)
        {
          IRecordInfo_RecordClear(lpRecInfo, pRecordData);
          pRecordData += psa->cbElements;
        }
        IRecordInfo_Release(lpRecInfo);
      }
    }
    else if (psa->fFeatures & FADF_BSTR)
    {
      BSTR* lpBstr = (BSTR*)psa->pvData + ulStartCell;

      while(ulCellCount--)
      {
        SysFreeString(*lpBstr);
        lpBstr++;
      }
    }
    else if (psa->fFeatures & FADF_VARIANT)
    {
      VARIANT* lpVariant = (VARIANT*)psa->pvData + ulStartCell;

      while(ulCellCount--)
      {
        HRESULT hRet = VariantClear(lpVariant);

        if (FAILED(hRet)) FIXME("VariantClear of element failed!\n");
        lpVariant++;
      }
    }
  }
  return S_OK;
}