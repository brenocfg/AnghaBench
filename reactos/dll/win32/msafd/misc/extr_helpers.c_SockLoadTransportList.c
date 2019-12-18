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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GlobalHeap ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WSAEINVAL ; 

INT
SockLoadTransportList(
    PWSTR *TransportList)
{
    ULONG	TransportListSize;
    HKEY	KeyHandle;
    LONG	Status;

    TRACE("Called\n");

    /* Open the Transports Key */
    Status = RegOpenKeyExW (HKEY_LOCAL_MACHINE,
                            L"SYSTEM\\CurrentControlSet\\Services\\Winsock\\Parameters",
                            0,
                            KEY_READ,
                            &KeyHandle);

    /* Check for error */
    if (Status) {
        ERR("Error reading transport list registry\n");
        return WSAEINVAL;
    }

    /* Get the Transport List Size */
    Status = RegQueryValueExW(KeyHandle,
                              L"Transports",
                              NULL,
                              NULL,
                              NULL,
                              &TransportListSize);

    /* Check for error */
    if (Status) {
        ERR("Error reading transport list registry\n");
        return WSAEINVAL;
    }

    /* Allocate Memory for the Transport List */
    *TransportList = HeapAlloc(GlobalHeap, 0, TransportListSize);

    /* Check for error */
    if (*TransportList == NULL) {
        ERR("Buffer allocation failed\n");
        return WSAEINVAL;
    }

    /* Get the Transports */
    Status = RegQueryValueExW (KeyHandle,
                               L"Transports",
                               NULL,
                               NULL,
                               (LPBYTE)*TransportList,
                               &TransportListSize);

    /* Check for error */
    if (Status) {
        ERR("Error reading transport list registry\n");
        HeapFree(GlobalHeap, 0, *TransportList);
        return WSAEINVAL;
    }

    /* Close key and return */
    RegCloseKey(KeyHandle);
    return 0;
}