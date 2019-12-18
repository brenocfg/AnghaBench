#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dwFileVersionMS; scalar_t__ dwFileVersionLS; } ;
typedef  TYPE_1__ VS_FIXEDFILEINFO ;
struct TYPE_5__ {scalar_t__ MinVersionLS; scalar_t__ MinVersionMS; scalar_t__ MaxVersionLS; scalar_t__ MaxVersionMS; int /*<<< orphan*/  File; } ;
typedef  TYPE_2__ MSISIGNATURE ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int DWORD ;

/* Variables and functions */
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int GetFileAttributesW (int /*<<< orphan*/ *) ; 
 int GetFileVersionInfoSizeW (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  GetFileVersionInfoW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  PathAddBackslashW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PathRemoveFileSpecW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VerQueryValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdupW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szBackSlash ; 

__attribute__((used)) static LPWSTR app_search_file(LPWSTR path, MSISIGNATURE *sig)
{
    VS_FIXEDFILEINFO *info;
    DWORD attr, handle, size;
    LPWSTR val = NULL;
    LPBYTE buffer;

    if (!sig->File)
    {
        PathRemoveFileSpecW(path);
        PathAddBackslashW(path);

        attr = GetFileAttributesW(path);
        if (attr != INVALID_FILE_ATTRIBUTES &&
            (attr & FILE_ATTRIBUTE_DIRECTORY))
            return strdupW(path);

        return NULL;
    }

    attr = GetFileAttributesW(path);
    if (attr == INVALID_FILE_ATTRIBUTES ||
        (attr & FILE_ATTRIBUTE_DIRECTORY))
        return NULL;

    size = GetFileVersionInfoSizeW(path, &handle);
    if (!size)
        return strdupW(path);

    buffer = msi_alloc(size);
    if (!buffer)
        return NULL;

    if (!GetFileVersionInfoW(path, 0, size, buffer))
        goto done;

    if (!VerQueryValueW(buffer, szBackSlash, (LPVOID)&info, &size) || !info)
        goto done;

    if (sig->MinVersionLS || sig->MinVersionMS)
    {
        if (info->dwFileVersionMS < sig->MinVersionMS)
            goto done;

        if (info->dwFileVersionMS == sig->MinVersionMS &&
            info->dwFileVersionLS < sig->MinVersionLS)
            goto done;
    }

    if (sig->MaxVersionLS || sig->MaxVersionMS)
    {
        if (info->dwFileVersionMS > sig->MaxVersionMS)
            goto done;

        if (info->dwFileVersionMS == sig->MaxVersionMS &&
            info->dwFileVersionLS > sig->MaxVersionLS)
            goto done;
    }

    val = strdupW(path);

done:
    msi_free(buffer);
    return val;
}