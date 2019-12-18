#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_1__* lpstbl; } ;
struct TYPE_18__ {void* pstrOleObjFileName; scalar_t__ dwOleID; scalar_t__ dwTypeID; int dwOleTypeNameLength; void* strOleTypeName; int dwOleObjFileNameLength; int dwDataLength; void* strUnknown; int /*<<< orphan*/ * pData; int /*<<< orphan*/  dwMetaFileHeight; int /*<<< orphan*/  dwMetaFileWidth; } ;
struct TYPE_17__ {int (* Get ) (TYPE_3__*,void*,int) ;} ;
typedef  TYPE_2__ OLECONVERT_OLESTREAM_DATA ;
typedef  TYPE_3__* LPOLESTREAM ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CONVERT10_E_OLESTREAM_FMT ; 
 scalar_t__ CONVERT10_E_OLESTREAM_GET ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ OLESTREAM_ID ; 
 scalar_t__ S_OK ; 
 int stub1 (TYPE_3__*,void*,int) ; 
 int stub10 (TYPE_3__*,void*,int) ; 
 int stub11 (TYPE_3__*,void*,int) ; 
 int stub2 (TYPE_3__*,void*,int) ; 
 int stub3 (TYPE_3__*,void*,int) ; 
 int stub4 (TYPE_3__*,void*,int) ; 
 int stub5 (TYPE_3__*,void*,int) ; 
 int stub6 (TYPE_3__*,void*,int) ; 
 int stub7 (TYPE_3__*,void*,int) ; 
 int stub8 (TYPE_3__*,void*,int) ; 
 int stub9 (TYPE_3__*,void*,int) ; 

__attribute__((used)) static HRESULT OLECONVERT_LoadOLE10(LPOLESTREAM pOleStream, OLECONVERT_OLESTREAM_DATA *pData, BOOL bStrem1)
{
	DWORD dwSize;
	HRESULT hRes = S_OK;
	int nTryCnt=0;
	int max_try = 6;

	pData->pData = NULL;
	pData->pstrOleObjFileName = NULL;

	for( nTryCnt=0;nTryCnt < max_try; nTryCnt++)
	{
	/* Get the OleID */
	dwSize = pOleStream->lpstbl->Get(pOleStream, (void *)&(pData->dwOleID), sizeof(pData->dwOleID));
	if(dwSize != sizeof(pData->dwOleID))
	{
		hRes = CONVERT10_E_OLESTREAM_GET;
	}
	else if(pData->dwOleID != OLESTREAM_ID)
	{
		hRes = CONVERT10_E_OLESTREAM_FMT;
	}
		else
		{
			hRes = S_OK;
			break;
		}
	}

	if(hRes == S_OK)
	{
		/* Get the TypeID... more info needed for this field */
		dwSize = pOleStream->lpstbl->Get(pOleStream, (void *)&(pData->dwTypeID), sizeof(pData->dwTypeID));
		if(dwSize != sizeof(pData->dwTypeID))
		{
			hRes = CONVERT10_E_OLESTREAM_GET;
		}
	}
	if(hRes == S_OK)
	{
		if(pData->dwTypeID != 0)
		{
			/* Get the length of the OleTypeName */
			dwSize = pOleStream->lpstbl->Get(pOleStream, (void *) &(pData->dwOleTypeNameLength), sizeof(pData->dwOleTypeNameLength));
			if(dwSize != sizeof(pData->dwOleTypeNameLength))
			{
				hRes = CONVERT10_E_OLESTREAM_GET;
			}

			if(hRes == S_OK)
			{
				if(pData->dwOleTypeNameLength > 0)
				{
					/* Get the OleTypeName */
					dwSize = pOleStream->lpstbl->Get(pOleStream, pData->strOleTypeName, pData->dwOleTypeNameLength);
					if(dwSize != pData->dwOleTypeNameLength)
					{
						hRes = CONVERT10_E_OLESTREAM_GET;
					}
				}
			}
			if(bStrem1)
			{
				dwSize = pOleStream->lpstbl->Get(pOleStream, (void *)&(pData->dwOleObjFileNameLength), sizeof(pData->dwOleObjFileNameLength));
				if(dwSize != sizeof(pData->dwOleObjFileNameLength))
				{
					hRes = CONVERT10_E_OLESTREAM_GET;
				}
			if(hRes == S_OK)
			{
					if(pData->dwOleObjFileNameLength < 1) /* there is no file name exist */
						pData->dwOleObjFileNameLength = sizeof(pData->dwOleObjFileNameLength);
					pData->pstrOleObjFileName = HeapAlloc(GetProcessHeap(), 0, pData->dwOleObjFileNameLength);
					if(pData->pstrOleObjFileName)
					{
						dwSize = pOleStream->lpstbl->Get(pOleStream, pData->pstrOleObjFileName, pData->dwOleObjFileNameLength);
						if(dwSize != pData->dwOleObjFileNameLength)
						{
							hRes = CONVERT10_E_OLESTREAM_GET;
						}
					}
					else
						hRes = CONVERT10_E_OLESTREAM_GET;
				}
			}
			else
			{
				/* Get the Width of the Metafile */
				dwSize = pOleStream->lpstbl->Get(pOleStream, (void *)&(pData->dwMetaFileWidth), sizeof(pData->dwMetaFileWidth));
				if(dwSize != sizeof(pData->dwMetaFileWidth))
				{
					hRes = CONVERT10_E_OLESTREAM_GET;
				}
			if(hRes == S_OK)
			{
				/* Get the Height of the Metafile */
				dwSize = pOleStream->lpstbl->Get(pOleStream, (void *)&(pData->dwMetaFileHeight), sizeof(pData->dwMetaFileHeight));
				if(dwSize != sizeof(pData->dwMetaFileHeight))
				{
					hRes = CONVERT10_E_OLESTREAM_GET;
				}
			}
			}
			if(hRes == S_OK)
			{
				/* Get the Length of the Data */
				dwSize = pOleStream->lpstbl->Get(pOleStream, (void *)&(pData->dwDataLength), sizeof(pData->dwDataLength));
				if(dwSize != sizeof(pData->dwDataLength))
				{
					hRes = CONVERT10_E_OLESTREAM_GET;
				}
			}

			if(hRes == S_OK) /* I don't know what this 8 byte information is. We have to figure out */
			{
				if(!bStrem1) /* if it is a second OLE stream data */
				{
					pData->dwDataLength -= 8;
					dwSize = pOleStream->lpstbl->Get(pOleStream, pData->strUnknown, sizeof(pData->strUnknown));
					if(dwSize != sizeof(pData->strUnknown))
					{
						hRes = CONVERT10_E_OLESTREAM_GET;
					}
				}
			}
			if(hRes == S_OK)
			{
				if(pData->dwDataLength > 0)
				{
					pData->pData = HeapAlloc(GetProcessHeap(),0,pData->dwDataLength);

					/* Get Data (ex. IStorage, Metafile, or BMP) */
					if(pData->pData)
					{
						dwSize = pOleStream->lpstbl->Get(pOleStream, (void *)pData->pData, pData->dwDataLength);
						if(dwSize != pData->dwDataLength)
						{
							hRes = CONVERT10_E_OLESTREAM_GET;
						}
					}
					else
					{
						hRes = CONVERT10_E_OLESTREAM_GET;
					}
				}
			}
		}
	}
	return hRes;
}