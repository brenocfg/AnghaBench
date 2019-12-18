#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  VirtualAddress; int /*<<< orphan*/  Size; } ;
struct TYPE_8__ {TYPE_5__* DataDirectory; } ;
struct TYPE_11__ {TYPE_1__ OptionalHeader; } ;
struct TYPE_9__ {TYPE_5__* DataDirectory; } ;
struct TYPE_10__ {TYPE_2__ OptionalHeader; } ;
typedef  TYPE_3__ IMAGE_NT_HEADERS64 ;
typedef  TYPE_4__ IMAGE_NT_HEADERS32 ;
typedef  TYPE_5__ IMAGE_DATA_DIRECTORY ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HDR_NT32 ; 
 int HDR_NT64 ; 
 int IMAGEHLP_GetNTHeaders (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*) ; 
 size_t IMAGE_FILE_SECURITY_DIRECTORY ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL IMAGEHLP_GetSecurityDirOffset( HANDLE handle,
                                           DWORD *pdwOfs, DWORD *pdwSize )
{
    IMAGE_NT_HEADERS32 nt_hdr32;
    IMAGE_NT_HEADERS64 nt_hdr64;
    IMAGE_DATA_DIRECTORY *sd;
    int ret;

    ret = IMAGEHLP_GetNTHeaders(handle, NULL, &nt_hdr32, &nt_hdr64);

    if (ret == HDR_NT32)
        sd = &nt_hdr32.OptionalHeader.DataDirectory[IMAGE_FILE_SECURITY_DIRECTORY];
    else if (ret == HDR_NT64)
        sd = &nt_hdr64.OptionalHeader.DataDirectory[IMAGE_FILE_SECURITY_DIRECTORY];
    else
        return FALSE;

    TRACE("ret = %d size = %x addr = %x\n", ret, sd->Size, sd->VirtualAddress);

    *pdwSize = sd->Size;
    *pdwOfs = sd->VirtualAddress;

    return TRUE;
}