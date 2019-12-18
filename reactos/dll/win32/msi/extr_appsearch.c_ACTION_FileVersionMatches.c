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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {scalar_t__ MinVersionMS; scalar_t__ MinVersionLS; scalar_t__ MaxVersionMS; scalar_t__ MaxVersionLS; int /*<<< orphan*/  Languages; } ;
typedef  TYPE_2__ MSISIGNATURE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetFileVersionInfoSizeW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetFileVersionInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  HIWORD (scalar_t__) ; 
 int /*<<< orphan*/  LOWORD (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VerQueryValueW (void*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_languages (void*,int /*<<< orphan*/ ) ; 
 void* msi_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (void*) ; 
 int /*<<< orphan*/  szBackSlash ; 

__attribute__((used)) static UINT ACTION_FileVersionMatches(const MSISIGNATURE *sig, LPCWSTR filePath,
 BOOL *matches)
{
    UINT len;
    void *version;
    VS_FIXEDFILEINFO *info = NULL;
    DWORD zero, size = GetFileVersionInfoSizeW( filePath, &zero );

    *matches = FALSE;

    if (!size) return ERROR_SUCCESS;
    if (!(version = msi_alloc( size ))) return ERROR_OUTOFMEMORY;

    if (GetFileVersionInfoW( filePath, 0, size, version ))
        VerQueryValueW( version, szBackSlash, (void **)&info, &len );

    if (info)
    {
        TRACE("comparing file version %d.%d.%d.%d:\n",
              HIWORD(info->dwFileVersionMS),
              LOWORD(info->dwFileVersionMS),
              HIWORD(info->dwFileVersionLS),
              LOWORD(info->dwFileVersionLS));
        if (info->dwFileVersionMS < sig->MinVersionMS
            || (info->dwFileVersionMS == sig->MinVersionMS &&
                info->dwFileVersionLS < sig->MinVersionLS))
        {
            TRACE("less than minimum version %d.%d.%d.%d\n",
                   HIWORD(sig->MinVersionMS),
                   LOWORD(sig->MinVersionMS),
                   HIWORD(sig->MinVersionLS),
                   LOWORD(sig->MinVersionLS));
        }
        else if ((sig->MaxVersionMS || sig->MaxVersionLS) &&
                 (info->dwFileVersionMS > sig->MaxVersionMS ||
                  (info->dwFileVersionMS == sig->MaxVersionMS &&
                   info->dwFileVersionLS > sig->MaxVersionLS)))
        {
            TRACE("greater than maximum version %d.%d.%d.%d\n",
                   HIWORD(sig->MaxVersionMS),
                   LOWORD(sig->MaxVersionMS),
                   HIWORD(sig->MaxVersionLS),
                   LOWORD(sig->MaxVersionLS));
        }
        else if (!match_languages( version, sig->Languages ))
        {
            TRACE("languages %s not supported\n", debugstr_w( sig->Languages ));
        }
        else *matches = TRUE;
    }
    msi_free( version );
    return ERROR_SUCCESS;
}