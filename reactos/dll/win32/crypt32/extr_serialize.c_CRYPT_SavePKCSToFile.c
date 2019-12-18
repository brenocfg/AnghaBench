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
struct TYPE_3__ {int /*<<< orphan*/  cbData; scalar_t__ pbData; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ CERT_BLOB ;
typedef  void* BOOL ;

/* Variables and functions */
 void* CRYPT_SavePKCSToMem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ CryptMemAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 void* FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,void*) ; 
 void* WriteFile (void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL CRYPT_SavePKCSToFile(HCERTSTORE store,
 DWORD dwMsgAndCertEncodingType, void *handle)
{
    CERT_BLOB blob = { 0, NULL };
    BOOL ret;

    TRACE("(%p)\n", handle);

    ret = CRYPT_SavePKCSToMem(store, dwMsgAndCertEncodingType, &blob);
    if (ret)
    {
        blob.pbData = CryptMemAlloc(blob.cbData);
        if (blob.pbData)
        {
            ret = CRYPT_SavePKCSToMem(store, dwMsgAndCertEncodingType, &blob);
            if (ret)
                ret = WriteFile(handle, blob.pbData, blob.cbData,
                 &blob.cbData, NULL);
        }
        else
        {
            SetLastError(ERROR_OUTOFMEMORY);
            ret = FALSE;
        }
    }
    TRACE("returning %d\n", ret);
    return ret;
}