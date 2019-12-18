#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* ULONG_PTR ;
struct TYPE_7__ {void* dwLower; void* dwUpper; } ;
typedef  int /*<<< orphan*/  SecurePackage ;
typedef  int /*<<< orphan*/  SecHandle ;
typedef  int /*<<< orphan*/  SECURITY_STATUS ;
typedef  TYPE_1__* PSecHandle ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SEC_E_INSUFFICIENT_MEMORY ; 
 int /*<<< orphan*/  SEC_E_INVALID_HANDLE ; 
 int /*<<< orphan*/  SEC_E_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static SECURITY_STATUS SECUR32_makeSecHandle(PSecHandle phSec,
 SecurePackage *package, PSecHandle realHandle)
{
    SECURITY_STATUS ret;

    TRACE("%p %p %p\n", phSec, package, realHandle);

    if (phSec && package && realHandle)
    {
        PSecHandle newSec = HeapAlloc(GetProcessHeap(), 0, sizeof(SecHandle));

        if (newSec)
        {
            *newSec = *realHandle;
            phSec->dwUpper = (ULONG_PTR)package;
            phSec->dwLower = (ULONG_PTR)newSec;
            ret = SEC_E_OK;
        }
        else
            ret = SEC_E_INSUFFICIENT_MEMORY;
    }
    else
        ret = SEC_E_INVALID_HANDLE;
    return ret;
}