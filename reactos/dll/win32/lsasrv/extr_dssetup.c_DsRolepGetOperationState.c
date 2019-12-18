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
struct TYPE_3__ {int /*<<< orphan*/  OperationState; } ;
typedef  TYPE_1__* PDSROLE_OPERATION_STATE_INFO ;
typedef  scalar_t__ PDSROLER_PRIMARY_DOMAIN_INFORMATION ;
typedef  int /*<<< orphan*/  NET_API_STATUS ;
typedef  int /*<<< orphan*/  DSROLE_OPERATION_STATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DsRoleOperationIdle ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 TYPE_1__* midl_user_allocate (int) ; 

__attribute__((used)) static
NET_API_STATUS
DsRolepGetOperationState(
    PDSROLER_PRIMARY_DOMAIN_INFORMATION *DomainInfo)
{
    PDSROLE_OPERATION_STATE_INFO Buffer;

    Buffer = midl_user_allocate(sizeof(DSROLE_OPERATION_STATE_INFO));
    if (Buffer == NULL)
        return ERROR_OUTOFMEMORY;

    Buffer->OperationState = DsRoleOperationIdle;

    *DomainInfo = (PDSROLER_PRIMARY_DOMAIN_INFORMATION)Buffer;

    return ERROR_SUCCESS;
}