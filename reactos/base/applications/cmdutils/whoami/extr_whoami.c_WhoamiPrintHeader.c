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
typedef  char* PWSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ NoHeader ; 
 scalar_t__ PrintFormat ; 
 char* WhoamiLoadRcString (int) ; 
 scalar_t__ csv ; 
 int /*<<< orphan*/  wcslen (char*) ; 
 int /*<<< orphan*/  wprintf (char*,...) ; 

void WhoamiPrintHeader(int HeaderId)
{
    PWSTR Header = WhoamiLoadRcString(HeaderId);
    DWORD Length = wcslen(Header);

    if (NoHeader || PrintFormat == csv)
        return;

    wprintf(L"\n%s\n", Header);

    while (Length--)
        wprintf(L"-");

    wprintf(L"\n\n");
}