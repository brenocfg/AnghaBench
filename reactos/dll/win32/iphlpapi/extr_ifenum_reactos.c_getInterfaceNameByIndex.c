#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int if_descrlen; int /*<<< orphan*/  if_descr; } ;
struct TYPE_6__ {TYPE_1__ ent; } ;
struct TYPE_7__ {TYPE_2__ if_info; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_3__ IFInfo ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_READ_DATA ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closeTcpFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getInterfaceInfoByIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  openTcpFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const char *getInterfaceNameByIndex(DWORD index)
{
    IFInfo ifInfo;
    HANDLE tcpFile;
    char *interfaceName = NULL;
    NTSTATUS status = openTcpFile( &tcpFile, FILE_READ_DATA );

    if( NT_SUCCESS(status) ) {
        status = getInterfaceInfoByIndex( tcpFile, index, &ifInfo );

        if( NT_SUCCESS(status) ) {
            interfaceName = HeapAlloc( GetProcessHeap(), 0,
                                       ifInfo.if_info.ent.if_descrlen + 1 );
            if( interfaceName ) {
              memcpy(interfaceName, ifInfo.if_info.ent.if_descr, ifInfo.if_info.ent.if_descrlen);
              interfaceName[ifInfo.if_info.ent.if_descrlen] = '\0';
            }
        }

        closeTcpFile( tcpFile );
    }

    return interfaceName;
}