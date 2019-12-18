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
typedef  int /*<<< orphan*/  PNET_LUID ;
typedef  int /*<<< orphan*/  NETIO_STATUS ;
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertInterfaceAliasToLuid (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ utf8to16 (char const*) ; 

__attribute__((used)) static DWORD
InterfaceLuid(const char *iface_name, PNET_LUID luid)
{
    NETIO_STATUS status;
    LPWSTR wide_name = utf8to16(iface_name);

    if (wide_name)
    {
        status = ConvertInterfaceAliasToLuid(wide_name, luid);
        free(wide_name);
    }
    else
    {
        status = ERROR_OUTOFMEMORY;
    }
    return status;
}