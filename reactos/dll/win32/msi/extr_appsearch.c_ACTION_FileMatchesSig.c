#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ dwHighDateTime; scalar_t__ dwLowDateTime; } ;
struct TYPE_12__ {scalar_t__ nFileSizeLow; TYPE_2__ ftCreationTime; } ;
typedef  TYPE_4__ WIN32_FIND_DATAW ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {scalar_t__ dwLowDateTime; scalar_t__ dwHighDateTime; } ;
struct TYPE_9__ {scalar_t__ dwLowDateTime; scalar_t__ dwHighDateTime; } ;
struct TYPE_13__ {scalar_t__ MinSize; scalar_t__ MaxSize; scalar_t__ MaxVersionLS; scalar_t__ MaxVersionMS; scalar_t__ MinVersionLS; scalar_t__ MinVersionMS; TYPE_3__ MaxTime; TYPE_1__ MinTime; } ;
typedef  TYPE_5__ MSISIGNATURE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_FileVersionMatches (TYPE_5__ const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static UINT ACTION_FileMatchesSig(const MSISIGNATURE *sig,
 const WIN32_FIND_DATAW *findData, LPCWSTR fullFilePath, BOOL *matches)
{
    UINT rc = ERROR_SUCCESS;

    *matches = TRUE;
    /* assumes the caller has already ensured the filenames match, so check
     * the other fields..
     */
    if (sig->MinTime.dwLowDateTime || sig->MinTime.dwHighDateTime)
    {
        if (findData->ftCreationTime.dwHighDateTime <
         sig->MinTime.dwHighDateTime ||
         (findData->ftCreationTime.dwHighDateTime == sig->MinTime.dwHighDateTime
         && findData->ftCreationTime.dwLowDateTime <
         sig->MinTime.dwLowDateTime))
            *matches = FALSE;
    }
    if (*matches && (sig->MaxTime.dwLowDateTime || sig->MaxTime.dwHighDateTime))
    {
        if (findData->ftCreationTime.dwHighDateTime >
         sig->MaxTime.dwHighDateTime ||
         (findData->ftCreationTime.dwHighDateTime == sig->MaxTime.dwHighDateTime
         && findData->ftCreationTime.dwLowDateTime >
         sig->MaxTime.dwLowDateTime))
            *matches = FALSE;
    }
    if (*matches && sig->MinSize && findData->nFileSizeLow < sig->MinSize)
        *matches = FALSE;
    if (*matches && sig->MaxSize && findData->nFileSizeLow > sig->MaxSize)
        *matches = FALSE;
    if (*matches && (sig->MinVersionMS || sig->MinVersionLS ||
     sig->MaxVersionMS || sig->MaxVersionLS))
        rc = ACTION_FileVersionMatches(sig, fullFilePath, matches);
    return rc;
}