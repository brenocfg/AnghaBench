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
struct AsnDecodeSequenceItem {int const tag; int pointerOffset; int (* decodeFunc ) (int,int /*<<< orphan*/ *,int const*,int,int,int*,scalar_t__*) ;int offset; scalar_t__ size; scalar_t__ minSize; scalar_t__ optional; scalar_t__ hasPointer; } ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ALIGN_DWORD_PTR (scalar_t__) ; 
 int CRYPT_DECODE_ALLOC_FLAG ; 
 scalar_t__ CRYPT_E_ASN1_BADTAG ; 
 scalar_t__ CRYPT_E_ASN1_CORRUPT ; 
 int CRYPT_GetLen (int const*,int,int*) ; 
 int FALSE ; 
 int GET_LEN_BYTES (int const) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ NOERROR ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int TRUE ; 
 int stub1 (int,int /*<<< orphan*/ *,int const*,int,int,int*,scalar_t__*) ; 

__attribute__((used)) static BOOL CRYPT_AsnDecodeSequenceItems(DWORD dwCertEncodingType,
 struct AsnDecodeSequenceItem items[], DWORD cItem, const BYTE *pbEncoded,
 DWORD cbEncoded, DWORD dwFlags, void *pvStructInfo, BYTE *nextData,
 DWORD *cbDecoded)
{
    BOOL ret;
    DWORD i, decoded = 0;
    const BYTE *ptr = pbEncoded;

    TRACE("%p, %d, %p, %d, %08x, %p, %p, %p\n", items, cItem, pbEncoded,
     cbEncoded, dwFlags, pvStructInfo, nextData, cbDecoded);

    for (i = 0, ret = TRUE; ret && i < cItem; i++)
    {
        if (cbEncoded - (ptr - pbEncoded) != 0)
        {
            DWORD nextItemLen;

            if ((ret = CRYPT_GetLen(ptr, cbEncoded - (ptr - pbEncoded),
             &nextItemLen)))
            {
                BYTE nextItemLenBytes = GET_LEN_BYTES(ptr[1]);

                if (ptr[0] == items[i].tag || !items[i].tag)
                {
                    if (nextData && pvStructInfo && items[i].hasPointer)
                    {
                        TRACE("Setting next pointer to %p\n",
                         nextData);
                        *(BYTE **)((BYTE *)pvStructInfo +
                         items[i].pointerOffset) = nextData;
                    }
                    if (items[i].decodeFunc)
                    {
                        if (pvStructInfo)
                            TRACE("decoding item %d\n", i);
                        else
                            TRACE("sizing item %d\n", i);
                        ret = items[i].decodeFunc(dwCertEncodingType,
                         NULL, ptr, 1 + nextItemLenBytes + nextItemLen,
                         dwFlags & ~CRYPT_DECODE_ALLOC_FLAG,
                         pvStructInfo ?  (BYTE *)pvStructInfo + items[i].offset
                         : NULL, &items[i].size);
                        if (ret)
                        {
                            if (items[i].size < items[i].minSize)
                                items[i].size = items[i].minSize;
                            else if (items[i].size > items[i].minSize)
                            {
                                /* Account for alignment padding */
                                items[i].size = ALIGN_DWORD_PTR(items[i].size);
                            }
                            TRACE("item %d size: %d\n", i, items[i].size);
                            if (nextData && items[i].hasPointer &&
                             items[i].size > items[i].minSize)
                                nextData += items[i].size - items[i].minSize;
                            ptr += 1 + nextItemLenBytes + nextItemLen;
                            decoded += 1 + nextItemLenBytes + nextItemLen;
                            TRACE("item %d: decoded %d bytes\n", i,
                             1 + nextItemLenBytes + nextItemLen);
                        }
                        else if (items[i].optional &&
                         GetLastError() == CRYPT_E_ASN1_BADTAG)
                        {
                            TRACE("skipping optional item %d\n", i);
                            items[i].size = items[i].minSize;
                            SetLastError(NOERROR);
                            ret = TRUE;
                        }
                        else
                            TRACE("item %d failed: %08x\n", i,
                             GetLastError());
                    }
                    else
                    {
                        TRACE("item %d: decoded %d bytes\n", i,
                         1 + nextItemLenBytes + nextItemLen);
                        ptr += 1 + nextItemLenBytes + nextItemLen;
                        decoded += 1 + nextItemLenBytes + nextItemLen;
                        items[i].size = items[i].minSize;
                    }
                }
                else if (items[i].optional)
                {
                    TRACE("skipping optional item %d\n", i);
                    items[i].size = items[i].minSize;
                }
                else
                {
                    TRACE("item %d: tag %02x doesn't match expected %02x\n",
                     i, ptr[0], items[i].tag);
                    SetLastError(CRYPT_E_ASN1_BADTAG);
                    ret = FALSE;
                }
            }
        }
        else if (items[i].optional)
        {
            TRACE("missing optional item %d, skipping\n", i);
            items[i].size = items[i].minSize;
        }
        else
        {
            TRACE("not enough bytes for item %d, failing\n", i);
            SetLastError(CRYPT_E_ASN1_CORRUPT);
            ret = FALSE;
        }
    }
    if (ret)
        *cbDecoded = decoded;
    TRACE("returning %d\n", ret);
    return ret;
}