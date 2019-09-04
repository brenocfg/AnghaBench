#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_6__ {struct TYPE_6__* Next; int /*<<< orphan*/  Name; } ;
struct TYPE_5__ {TYPE_2__* FirstKey; } ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  TYPE_1__* PINICACHESECTION ;
typedef  TYPE_2__* PINICACHEKEY ;

/* Variables and functions */
 scalar_t__ _wcsnicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ wcslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
PINICACHEKEY
IniCacheFindKey(
     PINICACHESECTION Section,
     PWCHAR Name,
     ULONG NameLength)
{
    PINICACHEKEY Key;

    Key = Section->FirstKey;
    while (Key != NULL)
    {
        if (NameLength == wcslen(Key->Name))
        {
            if (_wcsnicmp(Key->Name, Name, NameLength) == 0)
                break;
        }

        Key = Key->Next;
    }

    return Key;
}