#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * VARIANT ;
typedef  int ULONG ;
struct TYPE_11__ {int fFeatures; int cbElements; int /*<<< orphan*/ ** pvData; } ;
typedef  TYPE_1__ SAFEARRAY ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IRecordInfo ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/ * BYTE ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int FADF_BSTR ; 
 int FADF_CREATEVECTOR ; 
 int FADF_DATADELETED ; 
 int FADF_DISPATCH ; 
 int FADF_HAVEIID ; 
 int FADF_HAVEVARTYPE ; 
 int FADF_RECORD ; 
 int FADF_UNKNOWN ; 
 int FADF_VARIANT ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IRecordInfo_RecordCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IRecordInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int SAFEARRAY_GetCellCount (TYPE_1__*) ; 
 int /*<<< orphan*/  SAFEARRAY_GetHiddenDWORD (TYPE_1__*) ; 
 int /*<<< orphan*/  SAFEARRAY_SetHiddenDWORD (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SafeArrayGetIID (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SafeArrayGetRecordInfo (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SafeArraySetIID (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SafeArraySetRecordInfo (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SysAllocStringByteLen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SysStringByteLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantCopy (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int ignored_copy_features ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static HRESULT SAFEARRAY_CopyData(SAFEARRAY *psa, SAFEARRAY *dest)
{
  HRESULT hr = S_OK;

  if (!psa->pvData)
    return S_OK;

  if (!dest->pvData || psa->fFeatures & FADF_DATADELETED)
    return E_INVALIDARG;
  else
  {
    ULONG ulCellCount = SAFEARRAY_GetCellCount(psa);

    dest->fFeatures = (dest->fFeatures & FADF_CREATEVECTOR) | (psa->fFeatures & ~ignored_copy_features);

    if (psa->fFeatures & FADF_VARIANT)
    {
      VARIANT *src_var = psa->pvData;
      VARIANT *dest_var = dest->pvData;

      while(ulCellCount--)
      {
        HRESULT hRet;

        /* destination is cleared automatically */
        hRet = VariantCopy(dest_var, src_var);
        if (FAILED(hRet)) FIXME("VariantCopy failed with 0x%08x, element %u\n", hRet, ulCellCount);
        src_var++;
        dest_var++;
      }
    }
    else if (psa->fFeatures & FADF_BSTR)
    {
      BSTR *src_bstr = psa->pvData;
      BSTR *dest_bstr = dest->pvData;

      while(ulCellCount--)
      {
        SysFreeString(*dest_bstr);
        if (*src_bstr)
        {
          *dest_bstr = SysAllocStringByteLen((char*)*src_bstr, SysStringByteLen(*src_bstr));
          if (!*dest_bstr)
            return E_OUTOFMEMORY;
        }
        else
          *dest_bstr = NULL;
        src_bstr++;
        dest_bstr++;
      }
    }
    else if (psa->fFeatures & FADF_RECORD)
    {
      BYTE *dest_data = dest->pvData;
      BYTE *src_data = psa->pvData;
      IRecordInfo *record;

      SafeArrayGetRecordInfo(psa, &record);
      while (ulCellCount--)
      {
          /* RecordCopy() clears destination record */
          hr = IRecordInfo_RecordCopy(record, src_data, dest_data);
          if (FAILED(hr)) break;
          src_data += psa->cbElements;
          dest_data += psa->cbElements;
      }

      SafeArraySetRecordInfo(dest, record);
      /* This value is set to 32 bytes by default on descriptor creation,
         update with actual structure size. */
      dest->cbElements = psa->cbElements;
      IRecordInfo_Release(record);
    }
    else if (psa->fFeatures & (FADF_UNKNOWN|FADF_DISPATCH))
    {
      IUnknown **dest_unk = dest->pvData;
      IUnknown **src_unk = psa->pvData;

      /* release old iface, addref new one */
      while (ulCellCount--)
      {
          if (*dest_unk)
              IUnknown_Release(*dest_unk);
          *dest_unk = *src_unk;
          if (*dest_unk)
              IUnknown_AddRef(*dest_unk);
          src_unk++;
          dest_unk++;
      }
    }
    else
    {
      /* Copy the data over */
      memcpy(dest->pvData, psa->pvData, ulCellCount * psa->cbElements);
    }

    if (psa->fFeatures & FADF_HAVEIID)
    {
      GUID guid;
      SafeArrayGetIID(psa, &guid);
      SafeArraySetIID(dest, &guid);
    }
    else if (psa->fFeatures & FADF_HAVEVARTYPE)
    {
      SAFEARRAY_SetHiddenDWORD(dest, SAFEARRAY_GetHiddenDWORD(psa));
    }
  }

  return hr;
}