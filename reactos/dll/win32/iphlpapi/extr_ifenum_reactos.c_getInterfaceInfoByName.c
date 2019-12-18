#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  if_descrlen; scalar_t__ if_descr; } ;
struct TYPE_10__ {TYPE_1__ ent; } ;
struct TYPE_11__ {TYPE_2__ if_info; } ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_3__ IFInfo ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  getInterfaceInfoSet (int /*<<< orphan*/ ,TYPE_3__**,int*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

NTSTATUS getInterfaceInfoByName( HANDLE tcpFile, char *name, IFInfo *info ) {
    IFInfo *ifInfo;
    DWORD numInterfaces;
    int i;
    NTSTATUS status = getInterfaceInfoSet( tcpFile, &ifInfo, &numInterfaces );

    if( NT_SUCCESS(status) )
    {
        for( i = 0; i < numInterfaces; i++ ) {
            if( !strncmp((PCHAR)ifInfo[i].if_info.ent.if_descr, name, ifInfo[i].if_info.ent.if_descrlen) ) {
                memcpy( info, &ifInfo[i], sizeof(*info) );
                break;
            }
        }

        HeapFree(GetProcessHeap(), 0,ifInfo);

        return i < numInterfaces ? STATUS_SUCCESS : STATUS_UNSUCCESSFUL;
    }

    return status;
}