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
typedef  scalar_t__ (* UuidToStringFunc ) (int /*<<< orphan*/ *,unsigned char**) ;
typedef  scalar_t__ (* UuidCreateFunc ) (int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  UUID ;
typedef  int /*<<< orphan*/  (* RpcStringFreeFunc ) (unsigned char**) ;
typedef  scalar_t__ RPC_STATUS ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  scalar_t__ HMODULE ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SIGNATURE ; 
 int /*<<< orphan*/  CRYPT_NEWKEYSET ; 
 scalar_t__ CryptAcquireContextA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 scalar_t__ CryptGenKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  GetProcAddress (scalar_t__,char*) ; 
 scalar_t__ LoadLibraryA (char*) ; 
 int /*<<< orphan*/  MS_DEF_PROV_A ; 
 int /*<<< orphan*/  PROV_RSA_FULL ; 
 scalar_t__ RPC_S_OK ; 
 scalar_t__ RPC_S_UUID_LOCAL_ONLY ; 

__attribute__((used)) static HCRYPTPROV CRYPT_CreateKeyProv(void)
{
    HCRYPTPROV hProv = 0;
    HMODULE rpcrt = LoadLibraryA("rpcrt4");

    if (rpcrt)
    {
        UuidCreateFunc uuidCreate = (UuidCreateFunc)GetProcAddress(rpcrt,
         "UuidCreate");
        UuidToStringFunc uuidToString = (UuidToStringFunc)GetProcAddress(rpcrt,
         "UuidToStringA");
        RpcStringFreeFunc rpcStringFree = (RpcStringFreeFunc)GetProcAddress(
         rpcrt, "RpcStringFreeA");

        if (uuidCreate && uuidToString && rpcStringFree)
        {
            UUID uuid;
            RPC_STATUS status = uuidCreate(&uuid);

            if (status == RPC_S_OK || status == RPC_S_UUID_LOCAL_ONLY)
            {
                unsigned char *uuidStr;

                status = uuidToString(&uuid, &uuidStr);
                if (status == RPC_S_OK)
                {
                    BOOL ret = CryptAcquireContextA(&hProv, (LPCSTR)uuidStr,
                     MS_DEF_PROV_A, PROV_RSA_FULL, CRYPT_NEWKEYSET);

                    if (ret)
                    {
                        HCRYPTKEY key;

                        ret = CryptGenKey(hProv, AT_SIGNATURE, 0, &key);
                        if (ret)
                            CryptDestroyKey(key);
                    }
                    rpcStringFree(&uuidStr);
                }
            }
        }
        FreeLibrary(rpcrt);
    }
    return hProv;
}