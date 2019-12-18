#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ dwCheckPoint; scalar_t__ dwCurrentState; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  SetServiceStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ SvcStatus ; 

__attribute__((used)) static
VOID
UpdateServiceStatus(
    HANDLE hServiceStatus,
    DWORD NewStatus,
    DWORD Increment)
{
    if (Increment > 0)
        SvcStatus.dwCheckPoint += Increment;
    else
        SvcStatus.dwCheckPoint = 0;

    SvcStatus.dwCurrentState = NewStatus;
    SetServiceStatus(hServiceStatus, &SvcStatus);
}