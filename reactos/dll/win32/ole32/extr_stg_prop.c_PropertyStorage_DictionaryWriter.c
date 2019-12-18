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
struct DictionaryClosure {int bytesWritten; void* hr; } ;
typedef  int /*<<< orphan*/  propid ;
typedef  int /*<<< orphan*/  keyLen ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_2__ {scalar_t__ codePage; int /*<<< orphan*/  stm; } ;
typedef  TYPE_1__ PropertyStorage_impl ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CP_UNICODE ; 
 scalar_t__ FAILED (void*) ; 
 void* IStream_Write (int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ *) ; 
 void* PropertStorage_WriteWStringToStream (int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ *) ; 
 int PtrToUlong (void const*) ; 
 int /*<<< orphan*/  SUCCEEDED (void*) ; 
 int /*<<< orphan*/  StorageUtl_WriteDWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (void*) ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL PropertyStorage_DictionaryWriter(const void *key,
 const void *value, void *extra, void *closure)
{
    PropertyStorage_impl *This = extra;
    struct DictionaryClosure *c = closure;
    DWORD propid;
    ULONG count;

    assert(key);
    assert(closure);
    StorageUtl_WriteDWord((LPBYTE)&propid, 0, PtrToUlong(value));
    c->hr = IStream_Write(This->stm, &propid, sizeof(propid), &count);
    if (FAILED(c->hr))
        goto end;
    c->bytesWritten += sizeof(DWORD);
    if (This->codePage == CP_UNICODE)
    {
        DWORD keyLen, pad = 0;

        StorageUtl_WriteDWord((LPBYTE)&keyLen, 0,
         (lstrlenW((LPCWSTR)key) + 1) * sizeof(WCHAR));
        c->hr = IStream_Write(This->stm, &keyLen, sizeof(keyLen), &count);
        if (FAILED(c->hr))
            goto end;
        c->bytesWritten += sizeof(DWORD);
        c->hr = PropertStorage_WriteWStringToStream(This->stm, key, keyLen,
         &count);
        if (FAILED(c->hr))
            goto end;
        c->bytesWritten += keyLen * sizeof(WCHAR);
        if (keyLen % sizeof(DWORD))
        {
            c->hr = IStream_Write(This->stm, &pad,
             sizeof(DWORD) - keyLen % sizeof(DWORD), &count);
            if (FAILED(c->hr))
                goto end;
            c->bytesWritten += sizeof(DWORD) - keyLen % sizeof(DWORD);
        }
    }
    else
    {
        DWORD keyLen;

        StorageUtl_WriteDWord((LPBYTE)&keyLen, 0, strlen((LPCSTR)key) + 1);
        c->hr = IStream_Write(This->stm, &keyLen, sizeof(keyLen), &count);
        if (FAILED(c->hr))
            goto end;
        c->bytesWritten += sizeof(DWORD);
        c->hr = IStream_Write(This->stm, key, keyLen, &count);
        if (FAILED(c->hr))
            goto end;
        c->bytesWritten += keyLen;
    }
end:
    return SUCCEEDED(c->hr);
}