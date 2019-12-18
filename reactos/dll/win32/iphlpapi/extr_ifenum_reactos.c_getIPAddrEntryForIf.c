#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IFInfo ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getInterfaceInfoByIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getInterfaceInfoByName (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

NTSTATUS getIPAddrEntryForIf(HANDLE tcpFile,
                             char *name,
                             DWORD index,
                             IFInfo *ifInfo) {
    NTSTATUS status =
        name ?
        getInterfaceInfoByName( tcpFile, name, ifInfo ) :
        getInterfaceInfoByIndex( tcpFile, index, ifInfo );

    if (!NT_SUCCESS(status)) {
        ERR("getIPAddrEntryForIf returning %lx\n", status);
    }

    return status;
}