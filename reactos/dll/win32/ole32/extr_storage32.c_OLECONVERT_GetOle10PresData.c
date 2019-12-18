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
typedef  int WCHAR ;
struct TYPE_3__ {int dwTypeID; int* pData; int dwDataLength; scalar_t__ dwMetaFileHeight; scalar_t__ dwMetaFileWidth; void* dwOleID; } ;
typedef  TYPE_1__ OLECONVERT_OLESTREAM_DATA ;
typedef  int /*<<< orphan*/  LPSTORAGE ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IStorage_OpenStream (int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 void* OLESTREAM_ID ; 
 int STGM_READ ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ S_OK ; 

__attribute__((used)) static void OLECONVERT_GetOle10PresData(LPSTORAGE pStorage, OLECONVERT_OLESTREAM_DATA *pOleStreamData)
{

    HRESULT hRes;
    IStream *pStream;
    static const WCHAR wstrStreamName[] = {1, 'O', 'l', 'e', '1', '0', 'N', 'a', 't', 'i', 'v', 'e', 0};

    /* Initialize Default data for OLESTREAM */
    pOleStreamData[0].dwOleID = OLESTREAM_ID;
    pOleStreamData[0].dwTypeID = 2;
    pOleStreamData[1].dwOleID = OLESTREAM_ID;
    pOleStreamData[1].dwTypeID = 0;
    pOleStreamData[0].dwMetaFileWidth = 0;
    pOleStreamData[0].dwMetaFileHeight = 0;
    pOleStreamData[0].pData = NULL;
    pOleStreamData[1].pData = NULL;

    /* Open Ole10Native Stream */
    hRes = IStorage_OpenStream(pStorage, wstrStreamName, NULL,
        STGM_READ  | STGM_SHARE_EXCLUSIVE, 0, &pStream );
    if(hRes == S_OK)
    {

        /* Read Size and Data */
        IStream_Read(pStream, &(pOleStreamData->dwDataLength), sizeof(pOleStreamData->dwDataLength), NULL);
        if(pOleStreamData->dwDataLength > 0)
        {
            pOleStreamData->pData = HeapAlloc(GetProcessHeap(),0,pOleStreamData->dwDataLength);
            IStream_Read(pStream, pOleStreamData->pData, pOleStreamData->dwDataLength, NULL);
        }
        IStream_Release(pStream);
    }

}