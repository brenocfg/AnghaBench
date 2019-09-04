#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ Tag; void* DesiredAccess; } ;
struct TYPE_4__ {TYPE_1__ Handle; } ;
typedef  scalar_t__ SC_HANDLE ;
typedef  TYPE_2__* PMANAGER_HANDLE ;
typedef  void* DWORD ;

/* Variables and functions */
 void* ERROR_INVALID_HANDLE ; 
 void* ERROR_SUCCESS ; 
 scalar_t__ MANAGER_TAG ; 
 int /*<<< orphan*/  RtlMapGenericMask (void**,int /*<<< orphan*/ *) ; 
 scalar_t__ SERVICE_TAG ; 
 int /*<<< orphan*/  ScmManagerMapping ; 
 int /*<<< orphan*/  ScmServiceMapping ; 

__attribute__((used)) static DWORD
ScmCheckAccess(SC_HANDLE Handle,
               DWORD dwDesiredAccess)
{
    PMANAGER_HANDLE hMgr;

    hMgr = (PMANAGER_HANDLE)Handle;
    if (hMgr->Handle.Tag == MANAGER_TAG)
    {
        RtlMapGenericMask(&dwDesiredAccess,
                          &ScmManagerMapping);

        hMgr->Handle.DesiredAccess = dwDesiredAccess;

        return ERROR_SUCCESS;
    }
    else if (hMgr->Handle.Tag == SERVICE_TAG)
    {
        RtlMapGenericMask(&dwDesiredAccess,
                          &ScmServiceMapping);

        hMgr->Handle.DesiredAccess = dwDesiredAccess;

        return ERROR_SUCCESS;
    }

    return ERROR_INVALID_HANDLE;
}