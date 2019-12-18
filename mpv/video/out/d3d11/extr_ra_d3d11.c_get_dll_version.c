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
struct dll_version {void* revision; void* build; void* minor; void* major; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  dwFileVersionLS; int /*<<< orphan*/  dwFileVersionMS; } ;
typedef  TYPE_1__ VS_FIXEDFILEINFO ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  HRSRC ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FindResourceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* HIWORD (int /*<<< orphan*/ ) ; 
 void* LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* LockResource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SizeofResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VS_FILE_INFO ; 
 int /*<<< orphan*/  VS_VERSION_INFO ; 
 int /*<<< orphan*/  VerQueryValueW (void*,char*,void**,int*) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_memdup (void*,void*,int /*<<< orphan*/ ) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dll_version get_dll_version(HMODULE dll)
{
    void *ctx = talloc_new(NULL);
    struct dll_version ret = { 0 };

    HRSRC rsrc = FindResourceW(dll, MAKEINTRESOURCEW(VS_VERSION_INFO),
                               MAKEINTRESOURCEW(VS_FILE_INFO));
    if (!rsrc)
        goto done;
    DWORD size = SizeofResource(dll, rsrc);
    HGLOBAL res = LoadResource(dll, rsrc);
    if (!res)
        goto done;
    void *ptr = LockResource(res);
    if (!ptr)
        goto done;
    void *copy = talloc_memdup(ctx, ptr, size);

    VS_FIXEDFILEINFO *ffi;
    UINT ffi_len;
    if (!VerQueryValueW(copy, L"\\", (void**)&ffi, &ffi_len))
        goto done;
    if (ffi_len < sizeof(*ffi))
        goto done;

    ret.major = HIWORD(ffi->dwFileVersionMS);
    ret.minor = LOWORD(ffi->dwFileVersionMS);
    ret.build = HIWORD(ffi->dwFileVersionLS);
    ret.revision = LOWORD(ffi->dwFileVersionLS);

done:
    talloc_free(ctx);
    return ret;
}