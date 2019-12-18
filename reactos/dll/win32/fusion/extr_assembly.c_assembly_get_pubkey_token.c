#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hashdata ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
struct TYPE_7__ {int blobsz; TYPE_1__* tables; } ;
struct TYPE_6__ {int offset; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BCRYPT_ALG_HANDLE ;
typedef  TYPE_2__ ASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  ASSEMBLYTABLE ; 
 int /*<<< orphan*/  BCRYPT_SHA1_ALGORITHM ; 
 int /*<<< orphan*/  BCryptCloseAlgorithmProvider (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BCryptHash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ BCryptOpenAlgorithmProvider (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BYTES_PER_TOKEN ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MS_PRIMITIVE_PROVIDER ; 
 int /*<<< orphan*/  PublicKey ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  S_OK ; 
 int TOKEN_LENGTH ; 
 size_t TableFromToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * assembly_data_offset (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * assembly_get_blob (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  mdtAssembly ; 
 int /*<<< orphan*/  token_to_str (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT assembly_get_pubkey_token(ASSEMBLY *assembly, LPWSTR *token)
{
    ULONG i, size;
    LONG offset;
    BYTE hashdata[20], *pubkey, *ptr;
    BCRYPT_ALG_HANDLE alg;
    BYTE tokbytes[BYTES_PER_TOKEN];
    HRESULT hr = E_FAIL;
    LPWSTR tok;
    DWORD idx;

    *token = NULL;

    offset = assembly->tables[TableFromToken(mdtAssembly)].offset;
    if (offset == -1)
        return E_FAIL;

    ptr = assembly_data_offset(assembly, offset);
    if (!ptr)
        return E_FAIL;

    ptr += FIELD_OFFSET(ASSEMBLYTABLE, PublicKey);
    if (assembly->blobsz == sizeof(DWORD))
        idx = *(DWORD *)ptr;
    else
        idx = *(WORD *)ptr;

    pubkey = assembly_get_blob(assembly, idx, &size);

    if (BCryptOpenAlgorithmProvider(&alg, BCRYPT_SHA1_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0) != STATUS_SUCCESS)
        return E_FAIL;

    if (BCryptHash(alg, NULL, 0, pubkey, size, hashdata, sizeof(hashdata)) != STATUS_SUCCESS)
    {
        hr = E_FAIL;
        goto done;
    }

    size = sizeof(hashdata);
    for (i = size - 1; i >= size - 8; i--)
        tokbytes[size - i - 1] = hashdata[i];

    if (!(tok = heap_alloc((TOKEN_LENGTH + 1) * sizeof(WCHAR))))
    {
        hr = E_OUTOFMEMORY;
        goto done;
    }

    token_to_str(tokbytes, tok);

    *token = tok;
    hr = S_OK;

done:
    BCryptCloseAlgorithmProvider(alg, 0);
    return hr;
}