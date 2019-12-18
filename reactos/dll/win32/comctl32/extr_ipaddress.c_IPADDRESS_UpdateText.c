#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  Self; TYPE_1__* Part; } ;
struct TYPE_4__ {int /*<<< orphan*/  EditHwnd; } ;
typedef  TYPE_2__ IPADDRESS_INFO ;
typedef  int INT ;

/* Variables and functions */
 scalar_t__ GetWindowTextW (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcatW (char*,char const*) ; 

__attribute__((used)) static void IPADDRESS_UpdateText (const IPADDRESS_INFO *infoPtr)
{
    static const WCHAR zero[] = {'0', 0};
    static const WCHAR dot[]  = {'.', 0};
    WCHAR field[4];
    WCHAR ip[16];
    INT i;

    ip[0] = 0;

    for (i = 0; i < 4; i++) {
        if (GetWindowTextW (infoPtr->Part[i].EditHwnd, field, 4))
            strcatW(ip, field);
        else
            /* empty edit treated as zero */
            strcatW(ip, zero);
        if (i != 3)
            strcatW(ip, dot);
    }

    SetWindowTextW(infoPtr->Self, ip);
}