#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rc4_state {scalar_t__ hKey; int /*<<< orphan*/  hCryptProv; } ;
struct TYPE_2__ {scalar_t__ reserved; int /*<<< orphan*/  bVersion; int /*<<< orphan*/  bType; int /*<<< orphan*/  aiKeyAlg; } ;
typedef  TYPE_1__ PUBLICKEYSTRUC ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_RC4 ; 
 int /*<<< orphan*/  CRYPT_EXPORTABLE ; 
 int /*<<< orphan*/  CUR_BLOB_VERSION ; 
 int /*<<< orphan*/  CryptDestroyKey (scalar_t__) ; 
 int /*<<< orphan*/  CryptImportKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  PLAINTEXTKEYBLOB ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_malloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

void
rdssl_rc4_set_key(void* rc4_info, char* key, int len)
{
    struct rc4_state *info = rc4_info;
    BOOL ret;
    DWORD dwErr;
    BYTE * blob;
    PUBLICKEYSTRUC *desc;
    DWORD * keySize;
    BYTE * keyBuf;
    if (!rc4_info || !key || !len || !info->hCryptProv)
    {
        error("rdssl_rc4_set_key %p %p %d\n", rc4_info, key, len);
        return;
    }
    blob = g_malloc(sizeof(PUBLICKEYSTRUC) + sizeof(DWORD) + len, 0);
    if (!blob)
    {
        error("rdssl_rc4_set_key no memory\n");
        return;
    }
    desc = (PUBLICKEYSTRUC *)blob;
    keySize = (DWORD *)(blob + sizeof(PUBLICKEYSTRUC));
    keyBuf = blob + sizeof(PUBLICKEYSTRUC) + sizeof(DWORD);
    desc->aiKeyAlg = CALG_RC4;
    desc->bType = PLAINTEXTKEYBLOB;
    desc->bVersion = CUR_BLOB_VERSION;
    desc->reserved = 0;
    *keySize = len;
    memcpy(keyBuf, key, len);
    if (info->hKey)
    {
        CryptDestroyKey(info->hKey);
        info->hKey = 0;
    }
    ret = CryptImportKey(info->hCryptProv,
                         blob,
                         sizeof(PUBLICKEYSTRUC) + sizeof(DWORD) + len,
                         0,
                         CRYPT_EXPORTABLE,
                         &info->hKey);
    g_free(blob);
    if (!ret)
    {
        dwErr = GetLastError();
        error("CryptImportKey failed with %lx\n", dwErr);
    }
}