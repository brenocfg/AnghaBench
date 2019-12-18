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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
typedef  char* PWSTR ;
typedef  char* PWINSOCK_MAPPING ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GlobalHeap ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 int /*<<< orphan*/  WSAEINVAL ; 
 int /*<<< orphan*/  wcscat (char*,char*) ; 
 int /*<<< orphan*/  wcscpy (char*,char*) ; 
 int wcslen (char*) ; 

INT
SockLoadTransportMapping(
    PWSTR TransportName,
    PWINSOCK_MAPPING *Mapping)
{
    PWSTR               TransportKey;
    HKEY                KeyHandle;
    ULONG               MappingSize;
    LONG                Status;

    TRACE("TransportName %ws\n", TransportName);

    /* Allocate a Buffer */
    TransportKey = HeapAlloc(GlobalHeap, 0, (54 + wcslen(TransportName)) * sizeof(WCHAR));

    /* Check for error */
    if (TransportKey == NULL) {
        ERR("Buffer allocation failed\n");
        return WSAEINVAL;
    }

    /* Generate the right key name */
    wcscpy(TransportKey, L"System\\CurrentControlSet\\Services\\");
    wcscat(TransportKey, TransportName);
    wcscat(TransportKey, L"\\Parameters\\Winsock");

    /* Open the Key */
    Status = RegOpenKeyExW(HKEY_LOCAL_MACHINE, TransportKey, 0, KEY_READ, &KeyHandle);

    /* We don't need the Transport Key anymore */
    HeapFree(GlobalHeap, 0, TransportKey);

    /* Check for error */
    if (Status) {
        ERR("Error reading transport mapping registry\n");
        return WSAEINVAL;
    }

    /* Find out how much space we need for the Mapping */
    Status = RegQueryValueExW(KeyHandle, L"Mapping", NULL, NULL, NULL, &MappingSize);

    /* Check for error */
    if (Status) {
        ERR("Error reading transport mapping registry\n");
        return WSAEINVAL;
    }

    /* Allocate Memory for the Mapping */
    *Mapping = HeapAlloc(GlobalHeap, 0, MappingSize);

    /* Check for error */
    if (*Mapping == NULL) {
        ERR("Buffer allocation failed\n");
        return WSAEINVAL;
    }

    /* Read the Mapping */
    Status = RegQueryValueExW(KeyHandle, L"Mapping", NULL, NULL, (LPBYTE)*Mapping, &MappingSize);

    /* Check for error */
    if (Status) {
        ERR("Error reading transport mapping registry\n");
        HeapFree(GlobalHeap, 0, *Mapping);
        return WSAEINVAL;
    }

    /* Close key and return */
    RegCloseKey(KeyHandle);
    return 0;
}