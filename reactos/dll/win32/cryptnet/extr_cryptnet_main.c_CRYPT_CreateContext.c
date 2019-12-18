#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int cBlob; TYPE_1__* rgBlob; } ;
struct TYPE_7__ {int /*<<< orphan*/  pbData; } ;
typedef  void* HCERTSTORE ;
typedef  size_t DWORD ;
typedef  TYPE_1__ CRYPT_DATA_BLOB ;
typedef  TYPE_2__ CRYPT_BLOB_ARRAY ;
typedef  scalar_t__ BOOL ;
typedef  int /*<<< orphan*/  (* AddContextToStore ) (void*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_QUERY_FORMAT_FLAG_BINARY ; 
 int /*<<< orphan*/  CERT_QUERY_OBJECT_BLOB ; 
 int /*<<< orphan*/  CERT_STORE_ADD_ALWAYS ; 
 int /*<<< orphan*/  CERT_STORE_CREATE_NEW_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_MEMORY ; 
 int /*<<< orphan*/  CRYPT_E_NO_MATCH ; 
 void* CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ ) ; 
 scalar_t__ CryptQueryObject (int /*<<< orphan*/ ,TYPE_1__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const**) ; 
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 scalar_t__ decode_base64_blob (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static BOOL CRYPT_CreateContext(const CRYPT_BLOB_ARRAY *pObject,
 DWORD dwExpectedContentTypeFlags, AddContextToStore addFunc, void **ppvContext)
{
    BOOL ret = TRUE;
    CRYPT_DATA_BLOB blob;

    if (!pObject->cBlob)
    {
        SetLastError(ERROR_INVALID_DATA);
        *ppvContext = NULL;
        ret = FALSE;
    }
    else if (pObject->cBlob == 1)
    {
        if (decode_base64_blob(&pObject->rgBlob[0], &blob))
        {
            ret = CryptQueryObject(CERT_QUERY_OBJECT_BLOB, &blob,
             dwExpectedContentTypeFlags, CERT_QUERY_FORMAT_FLAG_BINARY, 0,
             NULL, NULL, NULL, NULL, NULL, (const void **)ppvContext);
            CryptMemFree(blob.pbData);
        }
        else
        {
            ret = CryptQueryObject(CERT_QUERY_OBJECT_BLOB, &pObject->rgBlob[0],
             dwExpectedContentTypeFlags, CERT_QUERY_FORMAT_FLAG_BINARY, 0,
             NULL, NULL, NULL, NULL, NULL, (const void **)ppvContext);
        }
        if (!ret)
        {
            SetLastError(CRYPT_E_NO_MATCH);
            ret = FALSE;
        }
    }
    else
    {
        HCERTSTORE store = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0,
         CERT_STORE_CREATE_NEW_FLAG, NULL);

        if (store)
        {
            DWORD i;
            const void *context;

            for (i = 0; i < pObject->cBlob; i++)
            {
                if (decode_base64_blob(&pObject->rgBlob[i], &blob))
                {
                    ret = CryptQueryObject(CERT_QUERY_OBJECT_BLOB, &blob,
                     dwExpectedContentTypeFlags, CERT_QUERY_FORMAT_FLAG_BINARY,
                     0, NULL, NULL, NULL, NULL, NULL, &context);
                    CryptMemFree(blob.pbData);
                }
                else
                {
                    ret = CryptQueryObject(CERT_QUERY_OBJECT_BLOB,
                     &pObject->rgBlob[i], dwExpectedContentTypeFlags,
                     CERT_QUERY_FORMAT_FLAG_BINARY, 0, NULL, NULL, NULL, NULL,
                     NULL, &context);
                }
                if (ret)
                {
                    if (!addFunc(store, context, CERT_STORE_ADD_ALWAYS, NULL))
                        ret = FALSE;
                }
                else
                {
                    SetLastError(CRYPT_E_NO_MATCH);
                    ret = FALSE;
                }
            }
        }
        else
            ret = FALSE;
        *ppvContext = store;
    }
    return ret;
}